# Zoids VS. decompilation

A matching decompilation of Zoids VS. for the GameCube (Japan, game ID `GZOJDA`). All 3,020 functions of the game (946,096 bytes) compile from the C and C++ sources in this repository to the same bytes as the original executable, and the rebuilt `main.dol` is identical to the original.

This repository contains no game data and no compilers.

## Requirements

- macOS or Linux, with Rust 1.88 or later.
- Your own copy of the game as a disc image, `game.iso` in the repository root (SHA-256 `d7a9457e6a195d01cd9595ec61f13d827b8bca092133991361667633e2680cfe`).
- Your own copy of the Metrowerks CodeWarrior for GameCube compilers, versions 1.2.5, 1.2.5n and 1.1p1.

Place each compiler, as an executable your system can run, at:

| Version | Path |
|---|---|
| 1.2.5 | `build/tools/mwcceppc-native` |
| 1.2.5n | `build/tools/mwcceppc-1.2.5n-native` |
| 1.1p1 | `build/tools/mwcceppc-1.1p1-native` |

To keep them elsewhere, pass `--compiler PATH` or set `MWCC=PATH` for the 1.2.5 compiler; the other two are looked up in the same directory under the names above.

## Usage

```sh
make verify   # compile every source file and compare each function with the original
make build    # write build/main.dol and check its SHA-1
```

Use a disc image at another path with `make verify ISO=path/to/game.iso`. A complete run reports `PASS 2909 C/C++ functions, 877436 bytes; complete DOL reconstruction matches 28ddef0987039a474a1b9a4a3157762e109d6fe8.`

## Build the English translation

Put your disc image at `build/Zoids vs. (Japan).iso`. Run:

```sh
cargo run --release --manifest-path tools/translate-rs/Cargo.toml --bin zvs-translate
```

This writes `build/Zoids VS (English).iso`. Pass `--iso PATH` and `--out PATH` to use other paths. The English text is in `translation/`.

## Layout

- `src/`: game code, Dolphin SDK, MusyX, MetroTRK and runtime sources.
- `include/`: headers.
- `tools/mwperm/`: the build and verify tool.
- `translation/`: English text and textures.
- `tools/translate-rs/`: the translation builder.

## License

GNU AGPL 3.0 only (`AGPL-3.0-only`). See `LICENSE`. If you distribute a modified version, or run one for users over a network, you must release its source under the same license. If you use this project's code or findings in your own work, see `NOTICE` for how to credit it.
