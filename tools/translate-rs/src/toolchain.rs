use anyhow::{anyhow, bail, Context, Result};
use sha2::{Digest, Sha256};
use std::fs;
use std::io::{Cursor, Read};
use std::path::{Component, Path, PathBuf};
use std::time::Duration;

pub const COMPILERS_URL: &str = "https://files.decomp.dev/compilers_20251118.zip";
pub const COMPILERS_SHA256: &str =
    "69b0d4980a2eccea4ae6e70b486714b5190cb6c75e3bc7b8fb5878a8854d0d1c";
pub const WIBO_URL: &str = "https://github.com/decompals/wibo/releases/download/1.2.0/wibo-macos";
pub const WIBO_SHA256: &str = "2b3000ef6a7a490c24ccd71967735ae0005e218922e51806cca1b8d77fd3cf7c";

const FLAGS: [&str; 20] = [
    "-c",
    "-O4,p",
    "-inline",
    "auto",
    "-fp",
    "hardware",
    "-fp_contract",
    "on",
    "-enum",
    "int",
    "-proc",
    "gekko",
    "-Cpp_exceptions",
    "off",
    "-RTTI",
    "off",
    "-nodefaults",
    "-nosyspath",
    "-align",
    "powerpc",
];

const SDK_1_2_5N: [&str; 11] = [
    "gx", "dsp", "ai", "ar", "exi", "si", "pad", "dvd", "card", "vi", "musyx",
];

const FILES_1_2_5N: [&[&str]; 16] = [
    &["src", "runtime", "bootstrap.c"],
    &["src", "sdk", "os", "alarm.c"],
    &["src", "sdk", "os", "interrupt.c"],
    &["src", "sdk", "os", "message.c"],
    &["src", "sdk", "os", "memory_protection.c"],
    &["src", "sdk", "os", "mutex.c"],
    &["src", "sdk", "os", "reboot.c"],
    &["src", "sdk", "os", "thread.c"],
    &["src", "sdk", "os", "time.c"],
    &["src", "sdk", "os", "kernel.c"],
    &["src", "sdk", "os", "cache.c"],
    &["src", "sdk", "os", "error.c"],
    &["src", "sdk", "os", "font.c"],
    &["src", "sdk", "os", "sram.c"],
    &["src", "sdk", "os", "reset_switch.c"],
    &["src", "sdk", "os", "audio_system.c"],
];

pub fn flags(root: &Path) -> Vec<String> {
    let mut flags: Vec<String> = FLAGS.iter().map(|flag| flag.to_string()).collect();
    flags.push("-i".to_string());
    flags.push(root.join("include").to_string_lossy().into_owned());
    flags
}

fn relative_parts(root: &Path, path: &Path) -> Option<Vec<String>> {
    let path = fs::canonicalize(path).ok()?;
    let root = fs::canonicalize(root).ok()?;
    let relative = path.strip_prefix(&root).ok()?;
    Some(
        relative
            .components()
            .filter_map(|part| match part {
                Component::Normal(name) => Some(name.to_string_lossy().into_owned()),
                _ => None,
            })
            .collect(),
    )
}

fn starts_with(parts: &[String], prefix: &[&str]) -> bool {
    parts.len() >= prefix.len() && parts.iter().zip(prefix).all(|(part, name)| part == name)
}

pub fn flags_for_source(root: &Path, path: &Path) -> Vec<String> {
    let base = flags(root);
    let Some(parts) = relative_parts(root, path) else {
        return base;
    };
    if !starts_with(&parts, &["src", "sdk", "trk"]) {
        return base;
    }
    let index = base
        .iter()
        .position(|flag| flag == "-inline")
        .unwrap_or_default();
    let mut flags = base[..index].to_vec();
    flags.extend(["-inline", "deferred"].map(String::from));
    flags.extend_from_slice(&base[index + 2..]);
    flags.extend(["-sdata", "0", "-sdata2", "0"].map(String::from));
    if matches!(
        parts.last().map(String::as_str),
        Some("targimpl.c" | "dolphin_trk_glue.c")
    ) {
        flags.extend(["-opt", "nopeephole"].map(String::from));
    }
    flags
}

pub fn download(url: &str, expected: &str) -> Result<Vec<u8>> {
    let response = ureq::get(url)
        .timeout(Duration::from_secs(600))
        .call()
        .with_context(|| format!("download {url}"))?;
    let mut data = Vec::new();
    response.into_reader().read_to_end(&mut data)?;
    let digest: String = Sha256::digest(&data)
        .iter()
        .map(|byte| format!("{byte:02x}"))
        .collect();
    if digest != expected {
        bail!("Tool download failed its SHA-256 check: {url}");
    }
    Ok(data)
}

#[cfg(unix)]
fn make_executable(path: &Path) -> Result<()> {
    use std::os::unix::fs::PermissionsExt;
    fs::set_permissions(path, fs::Permissions::from_mode(0o755))?;
    Ok(())
}

#[cfg(not(unix))]
fn make_executable(_path: &Path) -> Result<()> {
    Ok(())
}

pub fn toolchain(
    work: &Path,
    compiler: Option<&Path>,
    wibo: Option<&Path>,
    version: &str,
) -> Result<(PathBuf, PathBuf)> {
    let compiler = match compiler {
        Some(compiler) => compiler.to_path_buf(),
        None => {
            let mut bundle =
                zip::ZipArchive::new(Cursor::new(download(COMPILERS_URL, COMPILERS_SHA256)?))?;
            for name in ["mwcceppc.exe", "lmgr326b.dll"] {
                let mut data = Vec::new();
                bundle
                    .by_name(&format!("GC/{version}/{name}"))
                    .with_context(|| format!("GC/{version}/{name} is not in the compiler bundle"))?
                    .read_to_end(&mut data)?;
                fs::write(work.join(name), data)?;
            }
            work.join("mwcceppc.exe")
        }
    };
    let wibo = match wibo {
        Some(wibo) => wibo.to_path_buf(),
        None => {
            if !cfg!(target_os = "macos") {
                bail!("Set WIBO or --wibo for this platform.");
            }
            let wibo = work.join("wibo");
            fs::write(&wibo, download(WIBO_URL, WIBO_SHA256)?)?;
            make_executable(&wibo)?;
            wibo
        }
    };
    if !compiler.is_file() || !wibo.is_file() {
        bail!("The compiler or Windows executable wrapper is unavailable.");
    }
    Ok((fs::canonicalize(compiler)?, fs::canonicalize(wibo)?))
}

pub fn cached_toolchain(
    tools: &Path,
    compiler: Option<&Path>,
    wibo: Option<&Path>,
    version: &str,
) -> Result<(PathBuf, PathBuf)> {
    let directory = tools.join("compilers").join(version);
    let cached_wibo = tools.join("wibo");
    let cached_compiler = directory.join("mwcceppc.exe");
    let wibo = wibo.or_else(|| cached_wibo.is_file().then_some(cached_wibo.as_path()));
    let compiler = compiler.or_else(|| {
        cached_compiler
            .is_file()
            .then_some(cached_compiler.as_path())
    });
    if compiler.is_some() {
        fs::create_dir_all(tools)?;
        return toolchain(tools, compiler, wibo, version);
    }
    fs::create_dir_all(&directory)?;
    let (compiler, downloaded) = toolchain(&directory, None, wibo, version)?;
    if wibo.is_some() {
        return Ok((compiler, downloaded));
    }
    fs::rename(&downloaded, &cached_wibo)?;
    Ok((compiler, fs::canonicalize(&cached_wibo)?))
}

pub fn compiler_for_source(
    root: &Path,
    path: &Path,
    compiler: &Path,
    wibo: &Path,
    work: &Path,
) -> Result<PathBuf> {
    let Some(parts) = relative_parts(root, path) else {
        return Ok(compiler.to_path_buf());
    };
    let names: Vec<&str> = parts.iter().map(String::as_str).collect();
    let version = if starts_with(&parts, &["src", "sdk", "trk"]) {
        "1.1p1"
    } else if (names.len() >= 3
        && names[0] == "src"
        && names[1] == "sdk"
        && SDK_1_2_5N.contains(&names[2]))
        || FILES_1_2_5N.contains(&names.as_slice())
    {
        "1.2.5n"
    } else {
        return Ok(compiler.to_path_buf());
    };
    let parent = compiler
        .parent()
        .ok_or_else(|| anyhow!("{} has no parent directory", compiler.display()))?;
    if parent.file_name().is_some_and(|name| name == version) {
        return Ok(compiler.to_path_buf());
    }
    if let Some(family) = parent.parent() {
        let sibling = family.join(version).join("mwcceppc.exe");
        if family.file_name().is_some_and(|name| name == "GC") && sibling.is_file() {
            return Ok(fs::canonicalize(sibling)?);
        }
    }
    let directory = work.join("compilers").join(version);
    fs::create_dir_all(&directory)?;
    let cached = directory.join("mwcceppc.exe");
    if !cached.is_file() {
        toolchain(&directory, None, Some(wibo), version)?;
    }
    Ok(fs::canonicalize(cached)?)
}
