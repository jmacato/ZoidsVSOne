use crate::cave::{self, branch, Cave};
use crate::elf::{Elf, Symbol};
use crate::iplfont::{self, DISC_PATH, KATAKANA_BASE, SWITCH_PATHS, TITLE_GLYPHS};
use crate::relocate::{relocate, relocate_at};
use crate::text::SET_PATHS;
use crate::toolchain::{compiler_for_source, flags_for_source};
use anyhow::{anyhow, bail, Context, Result};
use std::collections::BTreeMap;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

pub const NOP: [u8; 4] = [0x60, 0x00, 0x00, 0x00];

pub type Edit = (&'static str, &'static str);

pub const SHIM: [(&str, &[Edit]); 4] = [
    (
        "ui/GetMenuMsgAdr.c",
        &[(
            "return TXT_Menu_dat + offset;",
            "return *(char **)TXT_Menu_dat + offset;",
        )],
    ),
    (
        "ui/yes_no.c",
        &[
            (
                "strcpy(destination, TXT_Menu_dat + TXT_Menu[message]);",
                "strcpy(destination, *(char **)TXT_Menu_dat + TXT_Menu[message]);",
            ),
            ("    static s16 nn = -2;\n", ""),
            ("    if (message != nn) {", "    {"),
        ],
    ),
    (
        "ui/testnumedit.c",
        &[
            (
                "#include \"gx_tev.h\"\n",
                concat!(
                    "#include \"gx_tev.h\"\n#include \"game_text.h\"\n\n",
                    "typedef struct { f32 m[3][4]; } NameMatrix;\n\n",
                    "f32 testnumedit(HSD_JObj *pilot, HSD_JObj *zoid, char *pilot_name, char *zoid_name)\n",
                    "{\n",
                    "    NameMatrix matrix;\n",
                    "    f32 end;\n\n",
                    "    end = pilot->matrix[0][3] + putAscJobj(pilot, 1, pilot_name) + ascH[1][46] + ascH[1][46] + ascH[1][46];\n",
                    "    if (zoid_name == 0)\n",
                    "        return end;\n",
                    "    matrix = *(NameMatrix *)zoid->matrix;\n",
                    "    if (matrix.m[0][3] < end)\n",
                    "        matrix.m[0][3] = end;\n",
                    "    return putAscMtxLR(matrix.m, 1, zoid_name, 0);\n",
                    "}\n",
                ),
            ),
            (
                "s32 testnumedit(s32 x, s32 y, s32 value)",
                "s32 testnumedit_unused(s32 x, s32 y, s32 value)",
            ),
        ],
    ),
    (
        "ui/ttl_main.cpp",
        &[
            (
                "    memcpy(TXT_Menu_dat, data, TXT_Menu_size);\n    free(data);\n    return 1;",
                "    *(char **)TXT_Menu_dat = (char *)data;\n    return 1;",
            ),
            (
                concat!(
                    "    putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[1].selected_person].name);\n",
                    "    putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 1, -1), 1, Tea_zoiddat[IveSave[1].selected_zoid].name);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 0, Tea_zoiddat[IveSave[1].selected_zoid].health);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 1, Tea_zoiddat[IveSave[1].selected_zoid].armor);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 2, Tea_zoiddat[IveSave[1].selected_zoid].field_0056);",
                ),
                concat!(
                    "    ZoidData *zoid = &Tea_zoiddat[IveSave[1].selected_zoid];\n",
                    "    putAscJobjLR(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[1].selected_person].name, 1);\n",
                    "    putAscJobjLR(GetChild(menu1p->models[idx], 0, 1, 0, 1, -1), 1, zoid->name, 1);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 0, zoid->health);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 1, zoid->armor);\n",
                    "    menu_sDispVsEntryZoidStatusKind(1, 2, zoid->field_0056);",
                ),
            ),
            ("extern s32 testnumedit(s32 x, s32 y, s32 value);\n", ""),
            (
                "            value = testnumedit(-240, -150, value);",
                "            value = value;",
            ),
            (
                "void menu_sDispBattleEntryPersonZoidStatus(void)\n{",
                concat!(
                    "extern f32 testnumedit(HSD_JObj *pilot, HSD_JObj *zoid, char *pilot_name, char *zoid_name);\n\n",
                    "void menu_sDispBattleEntryPersonZoidStatus(void)\n{",
                ),
            ),
            (
                concat!(
                    "    putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 0, -1), 1, Tea_persondat[IveSave[0].selected_person].name);\n",
                    "    if (menuZoidBattleModeSingleTeam == 1)\n",
                    "        putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[0].partner_person].name);\n",
                    "    zoid = IveSave[0].selected_zoid;\n",
                    "    if (zoid != -1)\n",
                    "        putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 1, -1), 1, Tea_zoiddat[zoid].name);\n",
                    "    if (menuZoidBattleModeSingleTeam == 1) {\n",
                    "        zoid = IveSave[0].partner_zoid;\n",
                    "        if (zoid != -1)\n",
                    "            putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 1, -1), 1, Tea_zoiddat[zoid].name);\n",
                    "    }",
                ),
                concat!(
                    "    zoid = IveSave[0].selected_zoid;\n",
                    "    testnumedit(GetChild(menu1p->models[idx], 0, 0, 0, 0, -1), GetChild(menu1p->models[idx], 0, 0, 0, 1, -1),\n",
                    "                Tea_persondat[IveSave[0].selected_person].name, zoid != -1 ? Tea_zoiddat[zoid].name : 0);\n",
                    "    if (menuZoidBattleModeSingleTeam == 1) {\n",
                    "        zoid = IveSave[0].partner_zoid;\n",
                    "        testnumedit(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), GetChild(menu1p->models[idx], 0, 1, 0, 1, -1),\n",
                    "                    Tea_persondat[IveSave[0].partner_person].name, zoid != -1 ? Tea_zoiddat[zoid].name : 0);\n",
                    "    }",
                ),
            ),
        ],
    ),
];

pub const SHIM_FUNCTIONS: [(&str, &[&str]); 4] = [
    ("ui/GetMenuMsgAdr.c", &["GetMenuMsgAdr"]),
    ("ui/yes_no.c", &["SetMenuMsgAdr"]),
    ("ui/testnumedit.c", &["testnumedit"]),
    (
        "ui/ttl_main.cpp",
        &[
            "TEA_defstatusload",
            "menu_sDispVsEntryPersonZoidStatus",
            "menu_sDispBattleEntryPersonZoidStatus",
        ],
    ),
];

pub const TEST_BOOT: [Edit; 2] = [
    (
        "    ret = 0;\n    menudispyesnoflag = 0;",
        "    ret = 8;\n    menudispyesnoflag = 0;",
    ),
    (
        "        if (sPad1->pressed_start != 0 || sPad2->pressed_start != 0)\n            break;",
        "        break;",
    ),
];

pub const TEST_BOOT_FUNCTIONS: [&str; 2] = ["ttlMain", "menufncPushStart"];

pub const FONT_SOURCE: &str = "sdk/os/font.c";

pub const FONT_FUNCTIONS: [&str; 2] = ["OSGetFontEncode", "OSLoadFont"];

pub const FONT_ENCODE: &str = concat!(
    "u16 OSGetFontEncode(void)\n",
    "{\n",
    "    static u16 fontEncode = 0xFFFF;\n",
    "    if (fontEncode <= 1) {\n",
    "        return fontEncode;\n",
    "    }\n",
    "    switch (*(int *)OSPhysicalToCached(0xCC)) {\n",
    "    case VI_NTSC:\n",
    "        fontEncode =\n",
    "            (__VIRegs[VI_DTV_STAT] & 2) ? OS_FONT_ENCODE_SJIS : OS_FONT_ENCODE_ANSI;\n",
    "        break;\n",
    "\n",
    "    case VI_PAL:\n",
    "    case VI_MPAL:\n",
    "    case VI_DEBUG:\n",
    "    case VI_DEBUG_PAL:\n",
    "    case VI_EURGB60:\n",
    "    default:\n",
    "        fontEncode = OS_FONT_ENCODE_ANSI;\n",
    "    }\n",
    "\n",
    "    return fontEncode;\n",
    "}",
);

pub const FONT_READ: &str = concat!(
    "static inline u32 ReadFont(void *img)\n",
    "{\n",
    "    if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {\n",
    "        ReadROM(img, OS_FONT_ROM_SIZE_SJIS, 0x1AFF00);\n",
    "    } else {\n",
    "        ReadROM(img, OS_FONT_ROM_SIZE_ANSI, 0x1FCF00);\n",
    "    }\n",
    "\n",
    "    return GetFontSize(img);\n",
    "}",
);

pub fn disc_font_read() -> String {
    let mut path = DISC_PATH.as_bytes().to_vec();
    path.push(0);
    path.resize(path.len().div_ceil(4) * 4, 0);
    let words = path.as_chunks::<4>().0;
    let names: String = words
        .iter()
        .enumerate()
        .map(|(i, word)| format!("    name[{i}] = 0x{:08X};\n", u32::from_be_bytes(*word)))
        .collect();
    format!(
        concat!(
            "static inline u32 ReadFont(void *img)\n{{\n    DVDFileInfo file;\n",
            "    u32 name[{}];\n\n{}",
            "    if (!DVDOpen((char *)name, &file))\n        return 0;\n",
            "    DVDReadPrio(&file, img, (s32)file.length, 0, 2);\n    DVDClose(&file);\n",
            "    return GetFontSize(img);\n}}",
        ),
        words.len(),
        names
    )
}

pub fn font_shim() -> Vec<(String, String)> {
    let pair = |old: &str, new: &str| (old.to_string(), new.to_string());
    vec![
        pair(
            "#include \"os_font.h\"\n",
            "#include \"os_font.h\"\n#include \"dvd_file.h\"\n",
        ),
        pair(
            FONT_ENCODE,
            "u16 OSGetFontEncode(void)\n{\n    return OS_FONT_ENCODE_SJIS;\n}",
        ),
        (FONT_READ.to_string(), disc_font_read()),
        pair(
            "        if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {\n            int fontCode;",
            "        if (0) {\n            int fontCode;",
        ),
    ]
}

pub const SWITCH_FUNCTIONS: [&str; 4] = [
    "configGet",
    "configClear",
    "menu_sDispConfig",
    "menufncZoid_ConfigMenu",
];

pub const SAVED_FONT: usize = 0x168A;

/// Menu cursor value of the TEXT FONT entry; 0 to 5 are the game's entries and 6 is EXIT.
pub const FONT_ENTRY: usize = 7;

/// Offsets from the row centre to its label and from the label to the font name, as f32 bits.
const LABEL_X: u32 = 0xC0F0_0000;
const VALUE_X: u32 = 0x41DB_3333;
const WORD_GAP: u32 = 0x3F4C_CCCD;
const VALUE_GAP: u32 = 0x3F80_0000;
const LABEL_FONT: u32 = 4;
const VALUE_FONT: u32 = 3;

const ROW_LOOP: &str = concat!(
    "                sSetAnim1(archive, 5, item, i == csN ? 2 : 1);\n",
    "            jobjDispAll(item);\n",
    "        }\n",
);

const ROW_ANIMATION: &str = concat!(
    "        if (crO != crN) {\n",
    "            csA = wait.value[crO + 1];\n",
    "            if (csAO == csA && end != 0) {\n",
    "                crO = crN;\n",
    "                csA = next.value[crN + 1];\n",
    "                csAO = -1;\n",
    "            }\n",
    "        } else if (csA == select.value[crN + 1]) {\n",
    "            if (end != 0)\n",
    "                csA = next.value[crN + 1];\n",
    "        } else {\n",
    "            csA = next.value[crN + 1];\n",
    "        }\n",
);

const MENU_STEP: &str = concat!(
    "        getSubMenuT();\n",
    "        subMenu();\n",
    "        done = menu_sDispConfig(archive, flags);\n",
);

const MENU_MOVE: &str = concat!(
    "                if (sPad1->pressed_up != 0)\n",
    "                    csN--;\n",
    "                if (sPad1->pressed_down != 0)\n",
    "                    csN++;\n",
);

const MENU_CLAMP: &str = "            if (csN > 6)\n                csN = 0;\n";

const MENU_OPTIONS: &str = "            } else if (csN != 6) {\n                previous = sbN;";

const ROW_DECLARATIONS: &str = concat!(
    "extern void sMakeMatrix(HSD_JObj *joint);\n",
    "HSD_JObj *HSD_JObjLoadJoint(void *description);\n",
    "void HSD_JObjRemoveAll(HSD_JObj *joint);\n",
    "void HSD_JObjAddChild(HSD_JObj *joint, HSD_JObj *child);\n",
    "s32 sGetAnimJoint(void *context, HSD_JObj *target);\n",
    "void HSD_JObjAddAnim(HSD_JObj *joint, void *animation, void *material, void *shape);\n",
    "void HSD_JObjReqAnim(HSD_JObj *joint, f32 frame);\n",
    "void HSD_AObjSetRate(void *animation, f32 rate);\n",
    "void HiddenParts(HSD_JObj *joint, s32 hidden);\n",
    "f32 putAscMtxLR(f32 matrix[3][4], s32 font, char *text, s32 right_align);\n",
    "f32 getAscH_sp(s32 font, char *text, f32 spacing);\n\n",
    "s32 menu_sDispConfig(",
);

fn font_row() -> String {
    format!(
        concat!(
            "{loop_end}",
            "        {{\n",
            "            HSD_JObj *row = GetChild(list, 0, {entry}, -1, -1, -1);\n",
            "            u32 *table = *(u32 **)((u8 *)archive + 0x24);\n",
            "            u32 *model = (u32 *)((u32 *)table[0])[5];\n",
            "            u8 *last = (u8 *)GetChild(cursor, 0, 5, -1, -1, -1);\n",
            "            f32 place[30];\n",
            "            f32 mtx[3][4];\n",
            "            u8 *first;\n",
            "            u8 *second;\n",
            "            u8 *third;\n",
            "            volatile f32 gap;\n",
            "            volatile f32 step;\n",
            "            volatile f32 left;\n",
            "            volatile f32 total;\n",
            "            s32 pass;\n",
            "            volatile union {{ u32 u; f32 f; }} k;\n",
            "            u32 word[2];\n",
            "            s32 fresh = 0;\n",
            "            char *name;\n",
            "            char part[24];\n",
            "            s32 n;\n",
            "\n",
            "            if (row == 0) {{\n",
            "                u32 *desc = (u32 *)((u32 *)model[0])[2];\n",
            "                for (n = 0; n < 5; n++)\n",
            "                    desc = (u32 *)desc[3];\n",
            "                row = HSD_JObjLoadJoint(desc);\n",
            "                HSD_JObjRemoveAll(*(HSD_JObj **)((u8 *)row + 8));\n",
            "                *(HSD_JObj **)((u8 *)row + 8) = 0;\n",
            "                HSD_JObjAddChild(list, row);\n",
            "                HiddenParts(GetChild(row, 0, 0, -1, -1, -1), 1);\n",
            "                fresh = 1;\n",
            "            }}\n",
            "            first = (u8 *)GetChild(cursor, 0, 0, -1, -1, -1);\n",
            "            second = (u8 *)GetChild(cursor, 0, 1, -1, -1, -1);\n",
            "            third = (u8 *)GetChild(cursor, 0, 2, -1, -1, -1);\n",
            "            gap = *(f32 *)(second + 0x60) - *(f32 *)(first + 0x60);\n",
            "            step = *(f32 *)(third + 0x60) - *(f32 *)(second + 0x60);\n",
            "            if (gap < gap - gap ? step > gap : step < gap)\n",
            "                gap = step;\n",
            "            *(f32 *)((u8 *)place + 0x50) = *(f32 *)(last + 0x50);\n",
            "            *(f32 *)((u8 *)place + 0x60) = *(f32 *)(last + 0x60) + gap;\n",
            "            *(f32 *)((u8 *)place + 0x70) = *(f32 *)(last + 0x70);\n",
            "            jobjCopyPos((HSD_JObj *)place, row);\n",
            "            if (jobjAnim1(row) != 0 || fresh != 0) {{\n",
            "                u32 context[6];\n",
            "                n = csN == {entry} ? 2 : 1;\n",
            "                context[0] = (u32)list;\n",
            "                context[1] = 0;\n",
            "                context[2] = model[0];\n",
            "                context[3] = model[1] != 0 ? ((u32 *)model[1])[n] : 0;\n",
            "                context[4] = model[2] != 0 ? ((u32 *)model[2])[n] : 0;\n",
            "                context[5] = model[3] != 0 ? ((u32 *)model[3])[n] : 0;\n",
            "                if (sGetAnimJoint(context, GetChild(list, 0, 5, -1, -1, -1)) != 0) {{\n",
            "                    HSD_JObjAddAnim(row, (void *)context[3], (void *)context[4], (void *)context[5]);\n",
            "                    k.u = 0;\n",
            "                    HSD_JObjReqAnim(row, k.f);\n",
            "                    if (*(void **)((u8 *)row + 0x7C) != 0) {{\n",
            "                        k.u = 0x3F800000;\n",
            "                        HSD_AObjSetRate(*(void **)((u8 *)row + 0x7C), k.f);\n",
            "                    }}\n",
            "                }}\n",
            "            }}\n",
            "            if (crN != 5 && crO != 5) {{\n",
            "                jobjDispAll(row);\n",
            "                for (n = 0; n < 12; n++)\n",
            "                    ((f32 *)mtx)[n] = *(f32 *)((u8 *)row + 0x44 + n * 4);\n",
            "                k.u = 0x{label_x:08X};\n",
            "                mtx[0][3] += k.f;\n",
            "                left = mtx[0][3];\n",
            "                word[0] = 0x54455854;\n",
            "                word[1] = 0;\n",
            "                k.f = putAscMtxLR(mtx, {label_font}, (char *)word, 0);\n",
            "                mtx[0][3] += k.f;\n",
            "                k.u = 0x{word_gap:08X};\n",
            "                mtx[0][3] += k.f;\n",
            "                word[0] = 0x464F4E54;\n",
            "                putAscMtxLR(mtx, {label_font}, (char *)word, 0);\n",
            "                mtx[0][3] = left;\n",
            "                if (crN == {entry}) {{\n",
            "                    mtx[1][3] += gap;\n",
            "                    if (sbTA != 0 && sbTA != 1) {{\n",
            "                        SetAnimArc2(archive, 4, 0);\n",
            "                        sbTA = 0;\n",
            "                    }}\n",
            "                    if (jobjAnim(archive->models[4]) != 0) {{\n",
            "                        SetAnimArc2(archive, 4, 1);\n",
            "                        sbTA = 1;\n",
            "                    }}\n",
            "                    last = (u8 *)GetChild(archive->models[18], 0, 0, -1, -1, -1);\n",
            "                    *(f32 *)((u8 *)place + 0x50) = *(f32 *)(last + 0x50);\n",
            "                    *(f32 *)((u8 *)place + 0x60) = mtx[1][3];\n",
            "                    *(f32 *)((u8 *)place + 0x70) = *(f32 *)(last + 0x70);\n",
            "                    jobjCopyPos((HSD_JObj *)place, archive->models[4]);\n",
            "                    jobjDispAll(archive->models[4]);\n",
            "                    k.u = 0x{value_x:08X};\n",
            "                    mtx[0][3] += k.f;\n",
            "                    k.u = 0;\n",
            "                    total = k.f;\n",
            "                    for (pass = 0; pass < 2; pass++) {{\n",
            "                        name = *(char **)TXT_Menu_dat;\n",
            "                        while (name != 0 && *name != 0) {{\n",
            "                            n = 0;\n",
            "                            while (*name != 0 && *name != 32 && n < 23)\n",
            "                                part[n++] = *name++;\n",
            "                            part[n] = 0;\n",
            "                            if (pass == 0) {{\n",
            "                                k.u = 0;\n",
            "                                k.f = getAscH_sp({value_font}, part, k.f);\n",
            "                                total += k.f;\n",
            "                            }} else {{\n",
            "                                k.f = putAscMtxLR(mtx, {value_font}, part, 0);\n",
            "                                mtx[0][3] += k.f;\n",
            "                            }}\n",
            "                            while (*name == 32)\n",
            "                                name++;\n",
            "                            if (*name != 0) {{\n",
            "                                k.u = 0x{value_gap:08X};\n",
            "                                if (pass == 0)\n",
            "                                    total += k.f;\n",
            "                                else\n",
            "                                    mtx[0][3] += k.f;\n",
            "                            }}\n",
            "                        }}\n",
            "                        if (pass == 0) {{\n",
            "                            k.u = 0x3F000000;\n",
            "                            mtx[0][3] -= total * k.f;\n",
            "                        }}\n",
            "                    }}\n",
            "                }} else if (sbT == -1 && sbTO == -1) {{\n",
            "                    sbTA = -1;\n",
            "                }}\n",
            "            }}\n",
            "        }}\n",
        ),
        loop_end = ROW_LOOP,
        entry = FONT_ENTRY,
        label_x = LABEL_X,
        value_x = VALUE_X,
        word_gap = WORD_GAP,
        value_gap = VALUE_GAP,
        label_font = LABEL_FONT,
        value_font = VALUE_FONT,
    )
}

fn name_words(path: &str, count: usize) -> Vec<u32> {
    let mut raw = path.as_bytes().to_vec();
    raw.resize(count * 4, 0);
    raw.as_chunks::<4>()
        .0
        .iter()
        .map(|word| u32::from_be_bytes(*word))
        .collect()
}

pub fn name_select(paths: &[&str], indent: &str) -> (usize, String) {
    let count = paths
        .iter()
        .map(|path| path.len() / 4 + 1)
        .max()
        .unwrap_or(1);
    let words: Vec<Vec<u32>> = paths.iter().map(|path| name_words(path, count)).collect();
    let mut code = String::new();
    for (index, word) in words[0].iter().enumerate() {
        code.push_str(&format!("{indent}name[{index}] = 0x{word:08X};\n"));
    }
    for (font, other) in words.iter().enumerate().skip(1) {
        code.push_str(&format!("{indent}if (font == {font}) {{\n"));
        for (index, word) in other.iter().enumerate() {
            if *word != words[0][index] {
                code.push_str(&format!("{indent}    name[{index}] = 0x{word:08X};\n"));
            }
        }
        code.push_str(&format!("{indent}}}\n"));
    }
    (count, code)
}

pub fn switch_font_read() -> String {
    let (count, names) = name_select(&SWITCH_PATHS, "    ");
    format!(
        concat!(
            "static inline u32 ReadFont(void *img)\n{{\n    DVDFileInfo file;\n",
            "    u32 name[{}];\n    u32 font = IveSaveFlag[0x{:X}];\n\n{}",
            "    if (!DVDOpen((char *)name, &file))\n        return 0;\n",
            "    DVDReadPrio(&file, img, (s32)file.length, 0, 2);\n    DVDClose(&file);\n",
            "    return GetFontSize(img);\n}}",
        ),
        count, SAVED_FONT, names
    )
}

pub fn switch_font_shim() -> Vec<(String, String)> {
    let mut edits = font_shim();
    edits[0].1.push_str("extern u8 IveSaveFlag[];\n");
    edits[2].1 = switch_font_read();
    edits
}

pub fn switch_shim() -> Vec<(String, String)> {
    let (count, names) = name_select(&SET_PATHS, "            ");
    vec![
        (
            "    VsMode = IveSaveFlag.vs_mode;\n    configSet();\n}".to_string(),
            format!(
                concat!(
                    "    VsMode = IveSaveFlag.vs_mode;\n",
                    "    {{\n",
                    "        u32 name[{}];\n",
                    "        u32 font = IveSaveFlag.reserved_168A[0];\n\n",
                    "        if (font > 2) {{\n",
                    "            font = 0;\n",
                    "            IveSaveFlag.reserved_168A[0] = 0;\n",
                    "        }}\n",
                    "        if (*(char **)TXT_Menu_dat != 0 && font != TXT_Menu_dat[4]) {{\n",
                    "            TXT_Menu_dat[4] = font;\n",
                    "            sFontUn();\n",
                    "            sFontInit();\n",
                    "            free(*(char **)TXT_Menu_dat);\n",
                    "{}",
                    "            *(char **)TXT_Menu_dat = (char *)sReadFileU((char *)name, 0);\n",
                    "        }}\n",
                    "    }}\n",
                    "    configSet();\n}}",
                ),
                count, names
            ),
        ),
        (
            "void configGet(void)\n{".to_string(),
            "extern s32 sFontInit(void);\nextern void sFontUn(void);\n\nvoid configGet(void)\n{"
                .to_string(),
        ),
        (
            "    IveSaveFlag.vs_mode = 1;\n    configGet();\n}".to_string(),
            concat!(
                "    IveSaveFlag.vs_mode = 1;\n",
                "    IveSaveFlag.reserved_168A[0] = 0;\n",
                "    VolSe = 8;\n",
                "    VolBgm = 8;\n",
                "    VolVoice = 8;\n",
                "    rumble = 1;\n",
                "    VsTime = 3;\n",
                "    VsMode = 1;\n",
                "    configSet();\n}",
            )
            .to_string(),
        ),
        (
            "extern void sMakeMatrix(HSD_JObj *joint);\n\ns32 menu_sDispConfig(".to_string(),
            ROW_DECLARATIONS.to_string(),
        ),
        (ROW_LOOP.to_string(), font_row()),
        (
            ROW_ANIMATION.to_string(),
            ROW_ANIMATION
                .replace("crO + 1", "(crO > 5 ? -1 : crO) + 1")
                .replace("crN + 1", "(crN > 5 ? -1 : crN) + 1"),
        ),
        (
            MENU_STEP.to_string(),
            format!(
                concat!(
                    "        if (crN != {entry}) {{\n",
                    "            getSubMenuT();\n",
                    "            subMenu();\n",
                    "        }} else if (sPad1->left != 0 || sPad1->right != 0) {{\n",
                    "            configPut();\n",
                    "            if (sPad1->right != 0)\n",
                    "                IveSaveFlag.reserved_168A[0] = IveSaveFlag.reserved_168A[0] < 2 ? IveSaveFlag.reserved_168A[0] + 1 : 0;\n",
                    "            else\n",
                    "                IveSaveFlag.reserved_168A[0] = IveSaveFlag.reserved_168A[0] > 0 ? IveSaveFlag.reserved_168A[0] - 1 : 2;\n",
                    "            configGet();\n",
                    "            SeSelectB();\n",
                    "        }}\n",
                    "        done = menu_sDispConfig(archive, flags);\n",
                ),
                entry = FONT_ENTRY
            ),
        ),
        (
            MENU_MOVE.to_string(),
            concat!(
                "                if (sPad1->pressed_up != 0)\n",
                "                    csN = csN == 0 ? 6 : csN == 6 ? 7 : csN == 7 ? 5 : csN - 1;\n",
                "                if (sPad1->pressed_down != 0)\n",
                "                    csN = csN == 5 ? 7 : csN == 7 ? 6 : csN == 6 ? 0 : csN + 1;\n",
            )
            .to_string(),
        ),
        (MENU_CLAMP.to_string(), MENU_CLAMP.replace("csN > 6", "csN > 7")),
        (MENU_OPTIONS.to_string(), MENU_OPTIONS.replace("csN != 6", "csN < 6")),
    ]
}

pub struct Tools {
    pub root: PathBuf,
    pub compiler: PathBuf,
    pub wibo: PathBuf,
}

fn compiler_cache<'a>(tools: &'a Tools, work: &'a Path) -> &'a Path {
    tools
        .compiler
        .parent()
        .and_then(Path::parent)
        .filter(|directory| {
            directory
                .file_name()
                .is_some_and(|name| name == "compilers")
        })
        .and_then(Path::parent)
        .unwrap_or(work)
}

pub fn compile_object(tools: &Tools, path: &Path, original: &Path, work: &Path) -> Result<Elf> {
    let cache = compiler_cache(tools, work);
    let compiler = compiler_for_source(&tools.root, original, &tools.compiler, &tools.wibo, cache)?;
    let name = path
        .file_name()
        .ok_or_else(|| anyhow!("{} has no file name", path.display()))?
        .to_string_lossy();
    let stem = path
        .file_stem()
        .ok_or_else(|| anyhow!("{} has no file name", path.display()))?;
    let output = work.join(stem).with_extension("o");
    let result = Command::new(&tools.wibo)
        .arg(&compiler)
        .args(flags_for_source(&tools.root, original))
        .arg("-i")
        .arg(path.parent().unwrap_or(Path::new("")))
        .arg(path)
        .arg("-o")
        .arg(&output)
        .current_dir(&tools.root)
        .output()
        .with_context(|| format!("run {}", tools.wibo.display()))?;
    if !result.status.success() {
        bail!(
            "{name}: compile failed ({})\n{}{}",
            result.status,
            String::from_utf8_lossy(&result.stdout),
            String::from_utf8_lossy(&result.stderr)
        );
    }
    Elf::read(&output)
}

fn find(text: &[u8], pattern: &[u8], from: usize) -> Option<usize> {
    text[from..]
        .windows(pattern.len())
        .position(|window| window == pattern)
        .map(|at| from + at)
}

fn replace_once(text: &[u8], old: &str, new: &str, name: &str) -> Result<Vec<u8>> {
    let pattern = old.as_bytes();
    let first = find(text, pattern, 0);
    let second = first.and_then(|at| find(text, pattern, at + pattern.len()));
    let (Some(at), None) = (first, second) else {
        bail!("shim anchor not found once in {name}: {old:?}");
    };
    let mut output = text[..at].to_vec();
    output.extend_from_slice(new.as_bytes());
    output.extend_from_slice(&text[at + pattern.len()..]);
    Ok(output)
}

fn copy_tree(from: &Path, to: &Path) -> Result<()> {
    fs::create_dir_all(to).with_context(|| format!("create {}", to.display()))?;
    for entry in fs::read_dir(from).with_context(|| format!("read {}", from.display()))? {
        let entry = entry?;
        let target = to.join(entry.file_name());
        if entry.path().is_dir() {
            copy_tree(&entry.path(), &target)?;
        } else {
            fs::copy(entry.path(), &target)?;
        }
    }
    Ok(())
}

struct Source {
    name: &'static str,
    edits: Vec<(String, String)>,
    functions: Vec<&'static str>,
}

fn sources(test_boot: bool, switch: bool) -> Result<Vec<Source>> {
    let mut sources: Vec<Source> = SHIM
        .iter()
        .zip(&SHIM_FUNCTIONS)
        .map(|((name, edits), (_, functions))| Source {
            name,
            edits: edits
                .iter()
                .map(|(old, new)| (old.to_string(), new.to_string()))
                .collect(),
            functions: functions.to_vec(),
        })
        .collect();
    if test_boot {
        for source in sources.iter_mut().filter(|s| s.name == "ui/ttl_main.cpp") {
            source.edits.extend(
                TEST_BOOT
                    .iter()
                    .map(|(old, new)| (old.to_string(), new.to_string())),
            );
            source.functions.extend(TEST_BOOT_FUNCTIONS);
        }
    }
    if switch {
        for source in sources.iter_mut().filter(|s| s.name == "ui/ttl_main.cpp") {
            source.edits.extend(switch_shim());
            source.functions.extend(SWITCH_FUNCTIONS);
        }
    }
    sources.push(Source {
        name: FONT_SOURCE,
        edits: if switch {
            switch_font_shim()
        } else {
            font_shim()
        },
        functions: FONT_FUNCTIONS.to_vec(),
    });
    sources.push(Source {
        name: STAFF_SOURCE,
        edits: staff_shim(),
        functions: STAFF_FUNCTIONS.to_vec(),
    });
    sources.push(Source {
        name: TITLE_SOURCE,
        edits: title_shim()?,
        functions: TITLE_FUNCTIONS.to_vec(),
    });
    sources.push(Source {
        name: HELP_SOURCE,
        edits: help_shim(),
        functions: HELP_FUNCTIONS.to_vec(),
    });
    Ok(sources)
}

pub const STAFF_SOURCE: &str = "text/ending.c";
const STAFF_FUNCTIONS: [&str; 1] = ["dispAscii"];
const STAFF_SCROLL: &str = concat!(
    "        if (entry->scroll_y > 100.0f) {\n",
    "            entry->text[0] = 0;\n",
    "            entry->scroll_y = 0.0f;\n",
    "        }\n",
);
const STAFF_OUTLINE: u32 = 0x3E4C_CCCD;
const STAFF_SHADOWS: [(i8, i8); 1] = [(1, -1)];

pub fn staff_shim() -> Vec<(String, String)> {
    let mut code = format!(
        concat!(
            "{scroll}",
            "        if (entry->text[0] != 0 && entry->text[0] != 33) {{\n",
            "            volatile union {{ u32 u; f32 f; }} k;\n",
            "            volatile f32 x0;\n",
            "            volatile f32 y0;\n",
            "            volatile f32 x1;\n",
            "            volatile f32 y1;\n",
            "            volatile f32 d;\n",
            "            GXColor ink;\n",
            "            GXColor clear;\n",
            "\n",
            "            k.u = 0x{offset:08X};\n",
            "            d = k.f;\n",
            "            x0 = j0->matrix[0][3];\n",
            "            y0 = j0->matrix[1][3];\n",
            "            x1 = j1->matrix[0][3];\n",
            "            y1 = j1->matrix[1][3];\n",
            "            *(u32 *)&clear = 0;\n",
            "            *(u32 *)&ink = 0x000000FF;\n",
        ),
        scroll = STAFF_SCROLL,
        offset = STAFF_OUTLINE,
    );
    for (x, y) in STAFF_SHADOWS {
        let (sx, sy) = (if x < 0 { '-' } else { '+' }, if y < 0 { '-' } else { '+' });
        code.push_str(&format!(
            concat!(
                "            j0->matrix[0][3] = x0 {sx} d;\n",
                "            j0->matrix[1][3] = y0 {sy} d;\n",
                "            j1->matrix[0][3] = x1 {sx} d;\n",
                "            j1->matrix[1][3] = y1 {sy} d;\n",
                "            sPutFontRect(entry->text, j0, j1, ink, clear, 0, 2);\n",
            ),
            sx = sx,
            sy = sy,
        ));
    }
    code.push_str(concat!(
        "            j0->matrix[0][3] = x0;\n",
        "            j0->matrix[1][3] = y0;\n",
        "            j1->matrix[0][3] = x1;\n",
        "            j1->matrix[1][3] = y1;\n",
        "            *(u32 *)&ink = 0xFFFFFFFF;\n",
        "            sPutFontRect(entry->text, j0, j1, ink, clear, 0, 2);\n",
        "        }\n",
    ));
    vec![(STAFF_SCROLL.to_string(), code)]
}

pub const TITLE_SOURCE: &str = "ui/menu_sDispStart.c";
const TITLE_FUNCTIONS: [&str; 1] = ["menu_sDispStart"];
const TITLE_STRIP: &str = concat!(
    "            HSD_JObjDispAll(GetChild(menu1p->models[0], 0, -1, -1, -1, -1), 0, 7, 0);\n",
    "            menu_sDispStartPushStart();\n",
);
const TITLE_END: &str = "    HSD_EndRender();\n    debugmenudraw();\n";
/// The original copyright line, then the translation credit.
const TITLE_LINES: [&str; 2] = [
    "\u{FF69}1983-2002 TOMY  \u{FF69}1999-2001 SHO-PRO\u{FF77}MBS\u{FF77}JRK",
    "Decomp, Translation \u{FF69} Jumar Macato \u{FF77} AGPL-3.0 \u{FF77} Patch 1.0.0",
];
const TITLE_HEIGHT: f32 = 1.5;
const TITLE_TOP: f32 = -18.6;
const TITLE_STEP: f32 = 1.625;
const TITLE_SHADOW: f32 = 0.1;
const TITLE_WIDE: f32 = 80.0;

fn title_width(font: &iplfont::Font, line: &str) -> Result<u32> {
    let mut width = 0;
    for character in line.chars() {
        let place = match character {
            '\u{FF69}' => KATAKANA_BASE + 0xA9 - 0xA1,
            '\u{FF77}' => KATAKANA_BASE + 0xB7 - 0xA1,
            _ => {
                TITLE_GLYPHS
                    .iter()
                    .find(|glyph| char::from(glyph.0) == character)
                    .ok_or_else(|| {
                        anyhow!("title line uses {character:?}, which has no bold glyph")
                    })?
                    .1
            }
        };
        width += u32::from(font.advance(place));
    }
    Ok(width)
}

fn title_shim() -> Result<Vec<(String, String)>> {
    let font = iplfont::story_font("chakra")?;
    let scale = TITLE_HEIGHT / 24.0;
    let mut words = Vec::new();
    let mut lines = String::new();
    for (row, line) in TITLE_LINES.iter().enumerate() {
        let mut raw = crate::text::encode_cp932(&iplfont::title_text(line))?;
        raw.push(0);
        raw.resize(raw.len().div_ceil(4) * 4, 0);
        let first = words.len();
        words.extend(
            raw.as_chunks::<4>()
                .0
                .iter()
                .map(|word| u32::from_be_bytes(*word)),
        );
        let left = -(title_width(&font, line)? as f32) * scale / 2.0;
        let top = TITLE_TOP - TITLE_STEP * row as f32;
        lines.push_str(&format!(
            concat!(
                "            q.u = 0x{left:08X};\n",
                "            left = q.f;\n",
                "            q.u = 0x{top:08X};\n",
                "            top = q.f;\n",
                "            q.u = 0x{shadow:08X};\n",
                "            corner[0][20] = left + q.f;\n",
                "            corner[0][24] = top - q.f;\n",
                "            q.u = 0x{wide:08X};\n",
                "            corner[1][20] = corner[0][20] + q.f;\n",
                "            q.u = 0x{height:08X};\n",
                "            corner[1][24] = corner[0][24] - q.f;\n",
                "            *(u32 *)&ink = 0x000000FF;\n",
                "            sPutFontRect((char *)&word[{first}], corner[0], corner[1], &ink, &clear, 0, 2);\n",
                "            corner[0][20] = left;\n",
                "            corner[0][24] = top;\n",
                "            q.u = 0x{wide:08X};\n",
                "            corner[1][20] = left + q.f;\n",
                "            q.u = 0x{height:08X};\n",
                "            corner[1][24] = top - q.f;\n",
                "            *(u32 *)&ink = 0xFFFFFFFF;\n",
                "            sPutFontRect((char *)&word[{first}], corner[0], corner[1], &ink, &clear, 0, 2);\n",
            ),
            left = left.to_bits(),
            top = top.to_bits(),
            shadow = TITLE_SHADOW.to_bits(),
            wide = TITLE_WIDE.to_bits(),
            height = TITLE_HEIGHT.to_bits(),
            first = first,
        ));
    }
    let mut pass = format!(
        concat!(
            "    HSD_EndRender();\n",
            "    HSD_StartRender(0);\n",
            "    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {{\n",
            "        HSD_LObjSetCurrentAll(menu1p->lights);\n",
            "        HSD_LObjSetupInit(menu1p->camera);\n",
            "        GXSetCullMode(0);\n",
            "        if (menumode != 0) {{\n",
            "            typedef struct {{ u8 r, g, b, a; }} TitleInk;\n",
            "            extern void sPutFontRect(char *text, void *top_left, void *bottom_right, TitleInk *color, TitleInk *shadow, s32 alpha, s32 flags);\n",
            "            volatile union {{ u32 u; f32 f; }} q;\n",
            "            volatile s32 n;\n",
            "            volatile f32 left;\n",
            "            volatile f32 top;\n",
            "            f32 corner[2][32];\n",
            "            u32 word[{count}];\n",
            "            TitleInk ink;\n",
            "            TitleInk clear;\n",
            "\n",
        ),
        count = words.len(),
    );
    for (index, word) in words.iter().enumerate() {
        pass.push_str(&format!("            word[{index}] = 0x{word:08X};\n"));
    }
    pass.push_str(concat!(
        "            for (n = 0; n < 12; n++) {\n",
        "                corner[0][17 + n] = *(f32 *)((u8 *)GetChild(menu1p->models[0], 0, -1, -1, -1, -1) + 0x44 + n * 4);\n",
        "                corner[1][17 + n] = corner[0][17 + n];\n",
        "            }\n",
        "            *(u32 *)&clear = 0;\n",
    ));
    pass.push_str(&lines);
    pass.push_str(concat!(
        "        }\n",
        "        HSD_CObjEndCurrent();\n",
        "        GXSetCullMode(2);\n",
        "    }\n",
        "    HSD_EndRender();\n",
        "    debugmenudraw();\n",
    ));
    Ok(vec![
        (
            TITLE_STRIP.to_string(),
            format!(
                concat!(
                    "            {{\n",
                    "                extern void HiddenParts(HSD_JObj *joint, s32 hidden);\n",
                    "                HiddenParts(GetChild(menu1p->models[0], 0, 1, -1, -1, -1), 1);\n",
                    "            }}\n",
                    "{strip}",
                ),
                strip = TITLE_STRIP,
            ),
        ),
        (TITLE_END.to_string(), pass),
    ])
}

pub const HELP_SOURCE: &str = "ui/menu_sDispStartMsgWin.c";
const HELP_FUNCTIONS: [&str; 1] = ["menu_sDispStartMsgWin"];
const HELP_TEXT_RAISE: f32 = 0.6818;
const HELP_BAND_RAISE: f32 = 0.65;
const HELP_BODY: &str = concat!(
    "    jobjAnim(menu1p->models[7]);\n",
    "    HSD_JObjDispAll(window, 0, 7, 0);\n",
    "    if (menudispwinstr == 0)\n",
    "        return;\n",
    "    sprintf(text, \"%s \", menudispwinstr);\n",
    "    sPutFontRect(text, GetChild(menu1p->models[7], 0, 0, -1, -1, -1),\n",
    "                 GetChild(menu1p->models[7], 0, 0, 0, -1, -1),\n",
    "                 (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);\n",
);

pub fn help_shim() -> Vec<(String, String)> {
    vec![(
        HELP_BODY.to_string(),
        format!(
            concat!(
                "    jobjAnim(menu1p->models[7]);\n",
                "    {{\n",
                "        extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);\n",
                "        volatile union {{ u32 u; f32 f; }} q;\n",
                "        volatile f32 y;\n",
                "        volatile s32 n;\n",
                "        f32 corner[2][32];\n",
                "\n",
                "        for (n = 0; n < 12; n++) {{\n",
                "            corner[0][17 + n] = *(f32 *)((u8 *)GetChild(menu1p->models[7], 0, 0, -1, -1, -1) + 0x44 + n * 4);\n",
                "            corner[1][17 + n] = *(f32 *)((u8 *)GetChild(menu1p->models[7], 0, 0, 0, -1, -1) + 0x44 + n * 4);\n",
                "        }}\n",
                "        q.u = 0x{text:08X};\n",
                "        corner[0][24] += q.f;\n",
                "        corner[1][24] += q.f;\n",
                "        q.u = 0x{band:08X};\n",
                "        y = *(f32 *)((u8 *)window + 0x3C);\n",
                "        *(f32 *)((u8 *)window + 0x3C) = y + q.f;\n",
                "        HSD_JObjSetMtxDirtySub(window);\n",
                "        HSD_JObjDispAll(window, 0, 7, 0);\n",
                "        *(f32 *)((u8 *)window + 0x3C) = y;\n",
                "        HSD_JObjSetMtxDirtySub(window);\n",
                "        sprintf(text, \"%s \", menudispwinstr);\n",
                "        sPutFontRect(text, (HSD_JObj *)corner[0], (HSD_JObj *)corner[1],\n",
                "                     (GXColor){{255, 255, 255, 255}}, (GXColor){{0, 0, 0, 0}}, 0, 2);\n",
                "    }}\n",
            ),
            text = HELP_TEXT_RAISE.to_bits(),
            band = HELP_BAND_RAISE.to_bits(),
        ),
    )]
}

pub const KERNEL_SOURCE: &str = "sdk/os/kernel.c";

pub const KERNEL_FUNCTION: &str = "OSInit";

pub const KERNEL_ARENA: &str = "OSSetArenaLo(!BootInfo->arenaLo ? &__ArenaLo : BootInfo->arenaLo);";

pub const KERNEL_STACK: &str =
    "OSSetArenaLo((void *)(((u32)(char *)&_stack_addr + 0x1F) & 0xFFFFFFE0));";

pub fn kernel_shim(reference: &Elf) -> Result<Vec<(String, String)>> {
    let end = cave::ADDRESS + cave::CAPACITY as u32;
    let stack = original(reference, "_stack_addr")?.address;
    let rise = end
        .checked_sub(stack)
        .filter(|rise| rise + 0x1F < 0x8000 && end.is_multiple_of(32))
        .ok_or_else(|| anyhow!("the code cave end {end:08X} is out of reach of _stack_addr"))?;
    Ok(vec![
        (
            KERNEL_ARENA.to_string(),
            format!("OSSetArenaLo(!BootInfo->arenaLo ? (void *)0x{end:08X} : BootInfo->arenaLo);"),
        ),
        (
            KERNEL_STACK.to_string(),
            format!(
                "OSSetArenaLo((void *)(((u32)(char *)&_stack_addr + 0x{:X}) & 0xFFFFFFE0));",
                rise + 0x1F
            ),
        ),
    ])
}

pub struct Shim {
    pub patches: BTreeMap<u32, Vec<u8>>,
    pub cave: Cave,
    pub moved: BTreeMap<&'static str, (u32, usize)>,
}

fn compile_source(
    tools: &Tools,
    work: &Path,
    name: &str,
    edits: &[(String, String)],
) -> Result<Elf> {
    let original = tools.root.join("src").join(name);
    let path = work.join("src").join(name);
    let (Some(from), Some(to)) = (original.parent(), path.parent()) else {
        bail!("{name} has no directory");
    };
    if !to.exists() {
        copy_tree(from, to)?;
    }
    let mut text = fs::read(&path).with_context(|| format!("read {}", path.display()))?;
    for (old, new) in edits {
        text = replace_once(&text, old, new, name)?;
    }
    fs::write(&path, text)?;
    compile_object(tools, &path, &original, work)
}

fn original<'a>(reference: &'a Elf, name: &str) -> Result<&'a Symbol> {
    reference
        .named(name)
        .first()
        .copied()
        .ok_or_else(|| anyhow!("{name} is not in the original ELF"))
}

fn compiled_size(compiled: &Elf, function: &str, name: &str) -> Result<u32> {
    compiled
        .functions()
        .iter()
        .find(|item| item.name == function)
        .map(|item| item.size)
        .ok_or_else(|| anyhow!("{function} is not in the compiled {name}"))
}

fn in_place(compiled: &Elf, reference: &Elf, target: &Symbol, size: u32) -> Result<Vec<u8>> {
    let resized = Symbol {
        size,
        ..target.clone()
    };
    let mut code = relocate(compiled, reference, &resized)?;
    while code.len() < target.size as usize {
        code.extend_from_slice(&NOP);
    }
    Ok(code)
}

fn kernel_patch(reference: &Elf, tools: &Tools, work: &Path) -> Result<(u32, Vec<u8>)> {
    let edits = kernel_shim(reference)?;
    let compiled = compile_source(tools, work, KERNEL_SOURCE, &edits)?;
    let target = original(reference, KERNEL_FUNCTION)?;
    let size = compiled_size(&compiled, KERNEL_FUNCTION, KERNEL_SOURCE)?;
    if size != target.size {
        bail!(
            "{KERNEL_FUNCTION} with the arena above the code cave is {size} bytes, the original is {}",
            target.size
        );
    }
    Ok((
        target.address,
        in_place(&compiled, reference, target, size)?,
    ))
}

pub fn shim_code_with_cave(
    reference: &Elf,
    tools: &Tools,
    work: &Path,
    test_boot: bool,
    forced: &[&str],
) -> Result<Shim> {
    shim_code_with_switch(reference, tools, work, test_boot, forced, false)
}

pub fn shim_code_with_switch(
    reference: &Elf,
    tools: &Tools,
    work: &Path,
    test_boot: bool,
    forced: &[&str],
    switch: bool,
) -> Result<Shim> {
    let work = &fs::canonicalize(work)?;
    let mut patches = BTreeMap::new();
    let mut cave = Cave::default();
    let mut moved = BTreeMap::new();
    for Source {
        name,
        edits,
        functions,
    } in sources(test_boot, switch)?
    {
        let compiled = compile_source(tools, work, name, &edits)?;
        for function_name in functions {
            let target = original(reference, function_name)?;
            let size = compiled_size(&compiled, function_name, name)?;
            if size <= target.size && !forced.contains(&function_name) {
                patches.insert(
                    target.address,
                    in_place(&compiled, reference, target, size)?,
                );
                continue;
            }
            let address = cave.next();
            let code = relocate_at(&compiled, reference, target, address)?;
            cave.push(function_name, &code)?;
            let mut stub = branch(target.address, address)?.to_vec();
            while stub.len() < target.size as usize {
                stub.extend_from_slice(&NOP);
            }
            patches.insert(target.address, stub);
            moved.insert(function_name, (address, code.len()));
        }
    }
    if let Some(missing) = forced.iter().find(|name| !moved.contains_key(*name)) {
        bail!("{missing} is not a shim function, it cannot be forced into the code cave");
    }
    if !cave.is_empty() {
        let (address, code) = kernel_patch(reference, tools, work)?;
        patches.insert(address, code);
    }
    Ok(Shim {
        patches,
        cave,
        moved,
    })
}

pub fn shim_code(
    reference: &Elf,
    tools: &Tools,
    work: &Path,
    test_boot: bool,
) -> Result<BTreeMap<u32, Vec<u8>>> {
    let shim = shim_code_with_cave(reference, tools, work, test_boot, &[])?;
    if !shim.cave.is_empty() {
        bail!(
            "{} bytes of grown functions need the code cave, call shim_code_with_cave",
            shim.cave.data.len()
        );
    }
    Ok(shim.patches)
}
