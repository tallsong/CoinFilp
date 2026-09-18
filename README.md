# CoinFilp

A small coin-flip puzzle game written in C++ with Qt Widgets. Tap a coin to flip it and its four neighbours; turn every coin on the 4×4 board face-up (gold) to clear the level. There are 20 hand-authored levels.

<p align="center">
  <img src="img/Title.png" alt="CoinFilp title" width="240">
</p>

## Gameplay

- **Main menu** – a start button leads to the level picker.
- **Level picker** – a 4×5 grid of 20 numbered level buttons.
- **Play scene** – a 4×4 board of coins. Clicking a coin flips it together with the coins directly above, below, left and right of it (edges and corners simply have fewer neighbours). When all 16 coins are face-up, the board locks, a win sound plays and a "level completed" banner bounces into view.
- A **back** button in the bottom-right corner of the level picker and play scene returns to the previous screen. Each window also has a `start → quit` menu.

Every button press, coin flip and win is accompanied by a sound effect, and coins animate through eight frames when they flip.

## Building

### Requirements

- Qt 6 (tested with 6.4) with the `core`, `gui`, `widgets` and `multimedia` modules
- A C++17-capable compiler
- Code follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html); a `.clang-format` is included.
- `qmake6` (or Qt Creator)

Sound effects are played through `QSoundEffect`, so the Qt Multimedia module and one of its platform audio backends must be installed.

### With Qt Creator

Open `CoinFilp.pro`, pick a Qt 6 kit, and press **Run**.

### From the command line

```sh
mkdir build && cd build
qmake6 ../CoinFilp.pro   # plain `qmake` also works if it points at a Qt 6 install
make                     # or nmake / mingw32-make on Windows
./CoinFilp
```

All images and sounds are compiled into the binary through `img.qrc`, so the executable has no runtime asset dependencies beyond the Qt libraries themselves.

## Project layout

| File | Purpose |
| --- | --- |
| `main.cpp` | Creates the `QApplication` and shows the main scene. |
| `mainscene.h/.cpp/.ui` | Main menu window with the start button and background painting. |
| `chooselevelscene.h/.cpp` | Level picker; creates a `PlayScene` for the chosen level and handles returning from it. |
| `playscene.h/.cpp` | The game board: lays out the coins, applies the flip rule to neighbours, checks for the win condition and plays the win animation. |
| `mycoin.h/.cpp` | A `QPushButton` subclass representing one coin. Runs the eight-frame flip animation with a single `QTimer` and ignores clicks while animating or once the board is locked after a win. |
| `mypushbutton.h/.cpp` | Image-based `QPushButton` with an optional pressed image and a small bounce animation used by the start button. |
| `dataconfig.h/.cpp` | Holds the 20 level layouts as a `constexpr` table of 4×4 `bool` boards (`1` = face-up, `0` = face-down), looked up with `GetLevelBoard(level)`. |
| `constants.h` | Scene size, scene-switch delay and resource paths shared by more than one scene. |
| `qt_yield_fix.h` | Build workaround for Qt 6.10 with Xcode 26+/27 on Apple Silicon (see comment inside). |
| `.clang-format` | Google C++ style; run `clang-format -i *.cpp *.h` after editing. |
| `img.qrc`, `img/` | Qt resource file and the PNG/WAV assets it bundles. |
| `docs/` | Miscellaneous Qt notes (currently an example of re-implementing focus events on a `QLineEdit`). |

## Adding or editing levels

Level data lives in `dataconfig.cpp` as the `kLevels` table; entry `n - 1` is level `n`, and each inner array is one column of the board from top to bottom. To change a level, edit its entry. To add a level beyond 20, append an entry and bump `kLevelCount` in `dataconfig.h`; the level picker creates one button per level automatically.

## Acknowledgements

The game structure and artwork follow the classic "翻金币" (flip coins) Qt teaching project. Coin, board, button and background assets are in `img/`.
