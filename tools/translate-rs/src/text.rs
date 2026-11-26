use crate::{disc, Files};
use anyhow::{anyhow, bail, Context, Result};
use serde_json::Value;
use std::collections::HashMap;
use std::path::Path;

pub const TXT_MENU_TABLE: u32 = 0x800F_54F0;
pub const TXT_MENU_COUNT: usize = 1176;
pub const MESSAGE_LIMIT: usize = 179;
pub const SET_PATHS: [&str; 3] = ["etc/TXT_Menu.BIN", "etc/TXT_Menu.txt", "etc/TXT_Menu.HED"];
pub const LABEL_SLOT: usize = 48;

pub fn encode_cp932(text: &str) -> Result<Vec<u8>> {
    let (raw, _, unmappable) = encoding_rs::SHIFT_JIS.encode(text);
    let widened = text
        .chars()
        .any(|c| matches!(c, '\u{a5}' | '\u{203e}' | '\u{2212}'));
    if unmappable || widened {
        bail!("{text:?} does not encode as cp932");
    }
    Ok(raw.into_owned())
}

pub fn pad_lines(en: &str, ja: &str, newline: &str) -> String {
    let wanted = ja.matches(newline).count();
    let present = en.matches(newline).count();
    let mut padded = en.to_owned();
    for _ in present..wanted {
        padded.push_str(newline);
    }
    padded
}

pub fn load(translation: &Path, name: &str) -> Result<Vec<Value>> {
    load_items(&translation.join(name))
}

pub fn load_items(path: &Path) -> Result<Vec<Value>> {
    let raw = std::fs::read_to_string(path).with_context(|| format!("read {}", path.display()))?;
    serde_json::from_str(&raw).with_context(|| format!("parse {}", path.display()))
}

pub fn item_text<'a>(item: &'a Value, key: &str) -> &'a str {
    item.get(key).and_then(Value::as_str).unwrap_or("")
}

pub fn item_label(item: &Value) -> String {
    match item.get("id") {
        Some(Value::String(id)) => id.clone(),
        Some(id) => id.to_string(),
        None => String::from("?"),
    }
}

pub fn item_cap(item: &Value) -> Result<usize> {
    item.get("cap")
        .and_then(Value::as_u64)
        .map(|cap| cap as usize)
        .ok_or_else(|| anyhow!("{}: no cap", item_label(item)))
}

pub fn parse_hex(text: &str) -> Result<usize> {
    let digits = text
        .strip_prefix("0x")
        .or_else(|| text.strip_prefix("0X"))
        .unwrap_or(text);
    usize::from_str_radix(digits, 16).with_context(|| format!("{text:?} is not hexadecimal"))
}

pub fn build_messages(path: &Path) -> Result<(Vec<u8>, Vec<u32>, usize)> {
    encode_messages(&load_items(path)?)
}

pub fn encode_messages(items: &[Value]) -> Result<(Vec<u8>, Vec<u32>, usize)> {
    let (mut blobs, offsets, translated) = encode_message_sets(&[items], &[])?;
    let blob = blobs.pop().ok_or_else(|| anyhow!("no message set"))?;
    Ok((blob, offsets, translated))
}

fn message_bytes(item: &Value) -> Result<Vec<u8>> {
    let en = item_text(item, "en");
    let ja = item_text(item, "ja");
    let raw = if en.is_empty() {
        encode_cp932(ja)?
    } else {
        encode_cp932(&pad_lines(en, ja, "\r\n"))?
    };
    if raw.len() > MESSAGE_LIMIT {
        bail!(
            "message {} is {} bytes; the copy buffers hold {MESSAGE_LIMIT}",
            item_label(item),
            raw.len()
        );
    }
    Ok(raw)
}

pub fn encode_message_sets(
    sets: &[&[Value]],
    labels: &[String],
) -> Result<(Vec<Vec<u8>>, Vec<u32>, usize)> {
    let first = *sets.first().ok_or_else(|| anyhow!("no message set"))?;
    if sets.iter().any(|set| set.len() != first.len()) {
        bail!("the message sets differ in length");
    }
    if !labels.is_empty() && labels.len() != sets.len() {
        bail!("{} labels for {} message sets", labels.len(), sets.len());
    }
    let mut blobs = vec![Vec::new(); sets.len()];
    for (blob, label) in blobs.iter_mut().zip(labels) {
        let raw = encode_cp932(label)?;
        if raw.len() >= LABEL_SLOT {
            bail!("label {label:?} does not fit {LABEL_SLOT} bytes");
        }
        blob.extend_from_slice(&raw);
        blob.resize(LABEL_SLOT, 0);
    }
    let mut placed: HashMap<String, u32> = HashMap::new();
    let mut offsets = Vec::with_capacity(first.len());
    for (index, item) in first.iter().enumerate() {
        let key = item
            .get("offset")
            .ok_or_else(|| anyhow!("message {}: no offset", item_label(item)))?
            .to_string();
        if let Some(&offset) = placed.get(&key) {
            offsets.push(offset);
            continue;
        }
        let raws = sets
            .iter()
            .map(|set| message_bytes(&set[index]))
            .collect::<Result<Vec<_>>>()?;
        let slot = raws.iter().map(Vec::len).max().unwrap_or(0) + 2;
        let offset = u32::try_from(blobs[0].len())?;
        placed.insert(key, offset);
        offsets.push(offset);
        for (blob, raw) in blobs.iter_mut().zip(&raws) {
            blob.extend_from_slice(raw);
            blob.resize(offset as usize + slot, 0);
        }
    }
    let translated = first
        .iter()
        .filter(|item| !item_text(item, "en").is_empty())
        .count();
    Ok((blobs, offsets, translated))
}

pub fn field_bytes(item: &Value) -> Result<Vec<u8>> {
    let padded = pad_lines(item_text(item, "en"), item_text(item, "ja"), "\r\n");
    if !padded.is_ascii() {
        bail!("{}: {padded:?} is not ASCII", item_label(item));
    }
    let mut raw = padded.into_bytes();
    let original = encode_cp932(item_text(item, "ja"))?;
    if original.ends_with(b" ") && raw.len() < original.len() {
        raw.resize(original.len(), b' ');
    }
    let cap = item_cap(item)?;
    if raw.len() + 1 > cap {
        bail!(
            "{}: {} bytes do not fit in {}",
            item_label(item),
            raw.len(),
            cap as i64 - 1
        );
    }
    raw.resize(cap, 0);
    Ok(raw)
}

fn splice(data: &mut Vec<u8>, offset: usize, width: usize, new: Vec<u8>) {
    let start = offset.min(data.len());
    let end = (offset + width).min(data.len());
    data.splice(start..end, new);
}

pub fn apply_fields(iso: &Path, items: &[Value], files: &mut Files) -> Result<usize> {
    let mut count = 0;
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let data = field_bytes(item)?;
        let places = item
            .get("where")
            .and_then(Value::as_array)
            .ok_or_else(|| anyhow!("{}: no where list", item_label(item)))?;
        for place in places {
            let (path, offset) = place
                .as_str()
                .and_then(|place| place.rsplit_once(':'))
                .ok_or_else(|| anyhow!("{}: bad where entry {place}", item_label(item)))?;
            let offset = parse_hex(offset)?;
            if !files.contains_key(path) {
                files.insert(path.to_owned(), disc::read_file(iso, path)?);
            }
            if let Some(file) = files.get_mut(path) {
                splice(file, offset, data.len(), data.clone());
            }
        }
        count += 1;
    }
    Ok(count)
}

pub fn build_epilogue(items: &[Value]) -> Result<Vec<u8>> {
    let lines: Vec<&str> = items
        .iter()
        .map(|item| {
            let en = item_text(item, "en");
            let ja = item_text(item, "ja");
            if !en.is_empty() || ja.is_empty() {
                en
            } else {
                ja
            }
        })
        .collect();
    encode_cp932(&lines.join("\r\n").replace('\u{A9}', "\u{FF6A}"))
}

pub fn build_banner(iso: &Path, items: &[Value]) -> Result<Vec<u8>> {
    let mut data = disc::read_file(iso, "OPENING.BNR")?;
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let offset = parse_hex(item_text(item, "offset"))?;
        splice(&mut data, offset, item_cap(item)?, field_bytes(item)?);
    }
    Ok(data)
}

pub fn write_menu_table(dol: &mut [u8], offsets: &[u32]) -> Result<()> {
    let table: Vec<u8> = offsets
        .iter()
        .flat_map(|offset| offset.to_be_bytes())
        .collect();
    disc::dol_write(dol, TXT_MENU_TABLE, &table)
}

pub fn write_dol_strings(dol: &mut [u8], items: &[Value]) -> Result<usize> {
    let mut count = 0;
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let address = u32::try_from(parse_hex(item_text(item, "id"))?)?;
        disc::dol_write(dol, address, &field_bytes(item)?)?;
        count += 1;
    }
    Ok(count)
}

pub fn build_text(
    iso: &Path,
    translation: &Path,
    messages: &Path,
    dol: &mut [u8],
    files: &mut Files,
) -> Result<Vec<String>> {
    build_text_items(iso, translation, &load_items(messages)?, dol, files)
}

pub fn build_text_items(
    iso: &Path,
    translation: &Path,
    messages: &[Value],
    dol: &mut [u8],
    files: &mut Files,
) -> Result<Vec<String>> {
    build_text_sets(iso, translation, &[messages], &[], dol, files)
}

pub fn build_text_sets(
    iso: &Path,
    translation: &Path,
    sets: &[&[Value]],
    labels: &[String],
    dol: &mut [u8],
    files: &mut Files,
) -> Result<Vec<String>> {
    if sets.len() > SET_PATHS.len() {
        bail!(
            "{} message sets, the disc holds {}",
            sets.len(),
            SET_PATHS.len()
        );
    }
    let (blobs, offsets, translated) = encode_message_sets(sets, labels)?;
    write_menu_table(dol, &offsets)?;
    let strings = write_dol_strings(dol, &load(translation, "dol_strings.json")?)?;
    for (path, blob) in SET_PATHS.iter().zip(blobs) {
        files.insert((*path).to_string(), blob);
    }
    let map_info = apply_fields(iso, &load(translation, "map_info.json")?, files)?;
    let names = apply_fields(iso, &load(translation, "names.json")?, files)?;
    files.insert(
        String::from("epilogue/epilogue.txt"),
        build_epilogue(&load(translation, "epilogue.json")?)?,
    );
    files.insert(
        String::from("OPENING.BNR"),
        build_banner(iso, &load(translation, "banner.json")?)?,
    );
    Ok(vec![
        format!("{translated}/{} messages", offsets.len()),
        format!("{strings} DOL strings"),
        format!("{map_info} map info strings"),
        format!("{names} names"),
    ])
}
