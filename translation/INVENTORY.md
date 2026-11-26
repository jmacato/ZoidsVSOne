# Zoids VS. text inventory

Every place the game shows Japanese, how it is extracted, and how it goes back in. `tools/translate-rs` applies all of it.

## Script text

| Source | File | Entries | Notes |
| --- | --- | --- | --- |
| Menu, story, dialogue | `etc/TXT_Menu.BIN` -> `TXT_Menu.json` | 1176 (834 with text) | Loaded through the relocation shim, so English can be longer than the Japanese. 179 bytes per message. |
| Mission and battle info | `menu/map_info_dat/*.mg` -> `map_info.json` | 227 unique | Fixed fields: title 100, victory 80, defeat 80, unit/map name 32, briefing 112 bytes. Drawn with `sPutFontRect`, which shrinks text to fit its box. |
| Zoid, part, pilot names | `etc/n_Zoid.dat`, `n_Parts.dat`, `n_Person.dat` -> `names.json` | 310 unique | Drawn with the menu sprite font: uppercase A-Z, 0-9, `/-()&!?*+`, space and lowercase m only. List rows fit about 12 characters. |
| Staff roll | `epilogue/epilogue.txt` -> `epilogue.json` | 223 lines | Line count must stay the same (scroll timing). Japanese `!N` lines showed pre-rendered images from `credit.dat`; English lines drop the prefix and render as text. |
| DOL strings | `main.dol` -> `dol_strings.json` | 18 | Disc errors, memory card comments, Farm/Clear, Victory/Defeat, R/L page hints. Must fit the original byte size. |
| Disc banner | `OPENING.BNR` -> `banner.json` | 5 | Title, maker and description shown by the IPL and emulators. |

## Textures

Found with `tools/translate/textures.py` (dumps every HSD and TPL texture) and `tools/translate/ocr.py` (Tesseract `jpn` on all 1921 unique textures).

| Texture | Fix |
| --- | --- |
| `menu/title/title.dat` main menu labels, 共和国 / 帝国 | Repainted as REPUBLIC / EMPIRE from the sheet's own neon letters (`art/title_factions.py`). |
| `menu/saveload/saveload.dat` glyph atlas: プレイ時間, 所持ゾイド数, 共和国, 帝国, ファーム, クリア, オールクリア | Each mesh is rewritten to one quad that samples an English word drawn into free atlas space (`atlas_text.py`, `atlas_text.json`). |
| `disp/div/message.dat` glyph atlas: 任務失敗 | Same, as MISSION FAILED, widened 1.8x. |
| `menu/vs_menu/vs_menu.dat` 完了 button | Redrawn as DONE (`art/vs_done.py`). |
| `menu/demo/demosell00.dat`, `demosell01.dat` story portrait name tags (ザン, アルバーン and 9 more) | Rebuilt from the atlas's own Latin glyphs into free atlas space (`atlas_text.json` with `"glyphs": true`); right-side tags are right-anchored. |

Left as is:
- The ゾイドバーサス katakana under the ZOIDS VS. logo (title, save screen, banner, opening movie). It is part of the logo.
- Japanese glyph cells in the menu atlases (任務完了, 失敗, 決定 and others) that no mesh draws.
- The kana and kanji glyphs in the `ascii/*.dat` fonts. They only render when a string contains Japanese.
- `disp/message.dat`, `disp/partner*.dat`, `menu/entry.dat`, `menu/demo/demo2.dat`, `menu/vs_menu/new/*`, `*_bak*`: never loaded by the game.
- Voice acting (`voice/*.ADP`) is Japanese audio and out of scope.
