use anyhow::{anyhow, bail, Result};
use std::collections::BTreeMap;
use std::path::PathBuf;
use zvs_translate::elf::Elf;
use zvs_translate::shim::{shim_code_with_switch, Tools};
use zvs_translate::toolchain::cached_toolchain;
use zvs_translate::{
    atlas, cave, disc, iplfont, layout, layout_disc, story, text, textures, Files,
};

const USAGE: &str = "usage: zvs-translate [--root REPO] [--iso JAPAN_ISO] [--out ISO] [--messages JSON] [--tools DIR] [--font chakra|xolonium|saira] [--test-boot] [--no-fixed-height] [--no-font-switch]";

fn main() -> Result<()> {
    let mut values: BTreeMap<String, PathBuf> = BTreeMap::new();
    let mut test_boot = false;
    let mut fixed_height = true;
    let mut font_switch = true;
    let mut args = std::env::args().skip(1);
    while let Some(key) = args.next() {
        if key == "--test-boot" {
            test_boot = true;
            continue;
        }
        if key == "--no-fixed-height" {
            fixed_height = false;
            continue;
        }
        if key == "--no-font-switch" {
            font_switch = false;
            continue;
        }
        if ![
            "--root",
            "--iso",
            "--out",
            "--messages",
            "--tools",
            "--font",
        ]
        .contains(&key.as_str())
        {
            bail!("unknown option {key}\n{USAGE}");
        }
        values.insert(
            key,
            PathBuf::from(args.next().ok_or_else(|| anyhow!(USAGE))?),
        );
    }
    let root = match values.get("--root") {
        Some(root) => root.clone(),
        None => PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../.."),
    };
    let root = std::fs::canonicalize(root)?;
    let build = PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../../build");
    let iso = values
        .get("--iso")
        .cloned()
        .unwrap_or_else(|| build.join("Zoids vs. (Japan).iso"));
    let name = if test_boot {
        "Zoids VS (English, test boot).iso"
    } else {
        "Zoids VS (English).iso"
    };
    let out = values
        .get("--out")
        .cloned()
        .unwrap_or_else(|| build.join(name));
    let translation = root.join("translation");
    let messages = values
        .get("--messages")
        .cloned()
        .unwrap_or_else(|| translation.join("TXT_Menu.json"));
    let font = values.get("--font").map_or_else(
        || String::from("chakra"),
        |value| value.to_string_lossy().into_owned(),
    );
    let tools_dir = values
        .get("--tools")
        .cloned()
        .unwrap_or_else(|| build.join("tools"));

    let reference = Elf::new(disc::read_file(&iso, "zoidR.elf")?)?;
    let (compiler, wibo) = cached_toolchain(&tools_dir, None, None, "1.2.5")?;
    let work = std::env::temp_dir().join(format!("zvs-translate-{}", std::process::id()));
    std::fs::create_dir_all(&work)?;
    let shim = shim_code_with_switch(
        &reference,
        &Tools {
            root: root.clone(),
            compiler,
            wibo,
        },
        &work,
        test_boot,
        &[],
        font_switch,
    );
    std::fs::remove_dir_all(&work)?;
    let shim = shim?;

    let mut dol = disc::read_dol(&iso)?;
    for (address, code) in &shim.patches {
        disc::dol_write(&mut dol, *address, code)?;
    }
    let mut files = Files::new();
    let mut fonts = iplfont::font_order(&font)?;
    if !font_switch {
        fonts.truncate(1);
    }
    let items = text::load_items(&messages)?;
    let mut sets = Vec::new();
    let mut fixed = None;
    for (name, _) in &fonts {
        let mut items = items.clone();
        if fixed_height {
            let count = story::apply(&iso, name, &mut items)?;
            fixed.get_or_insert(count);
        }
        sets.push(items);
    }
    let sets: Vec<&[serde_json::Value]> = sets.iter().map(Vec::as_slice).collect();
    let labels: Vec<String> = fonts
        .iter()
        .filter(|_| font_switch)
        .map(|(_, label)| label.to_uppercase())
        .collect();
    let mut report =
        text::build_text_sets(&iso, &translation, &sets, &labels, &mut dol, &mut files)?;
    if let Some(fixed) = fixed {
        report.push(format!("{fixed} story messages at fixed height"));
    }
    for ((name, _), path) in fonts.iter().zip(iplfont::SWITCH_PATHS) {
        files.insert(path.to_string(), iplfont::story_font(name)?.encode()?);
    }
    let texture_count =
        textures::texture_patches_from(&translation.join("textures"), &iso, &mut files)?;
    let words = atlas::atlas_patches_from(&translation.join("atlas_text.json"), &iso, &mut files)?;
    report.push(format!("{texture_count} textures, {words} atlas words"));
    report.push(format!(
        "{} layout edits",
        layout::layout_patches(&iso, &mut files)?
    ));
    layout_disc::write_iso_with_cave(&iso, &out, &dol, &files, &shim.cave)?;
    for (name, (address, size)) in &shim.moved {
        println!("{name} moved to {address:08X}, {size} bytes");
    }
    println!(
        "{}, {} functions patched, {} of {} code cave bytes, {} files replaced -> {}",
        report.join(", "),
        shim.patches.len(),
        shim.cave.data.len(),
        cave::CAPACITY,
        files.len(),
        out.display()
    );
    Ok(())
}
