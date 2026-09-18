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

### macOS note

Qt releases before 6.5.3 try to link against Apple's `AGL` framework, which Xcode 15 and later no longer ship, producing `framework 'AGL' not found` at link time. `CoinFilp.pro` overrides the OpenGL link settings on macOS so the project links with those Qt versions. If you switch Qt versions, re-run qmake so the change is picked up.

All images and sounds are compiled into the binary through `img.qrc`, so the executable has no runtime asset dependencies beyond the Qt libraries themselves.

## Project layout

| File | Purpose |
| --- | --- |
| `main.cpp` | Creates the `QApplication` and shows the main scene. |
| `mainscene.h/.cpp/.ui` | Main menu window with the start button and background painting. |
| `chooselevelscene.h/.cpp` | Level picker; creates a `PlayScene` for the chosen level and handles returning from it. |
| `playscene.h/.cpp` | The game board: lays out the coins, applies the flip rule to neighbours, checks for the win condition and plays the win animation. |
| `mycoin.h/.cpp` | A `QPushButton` subclass representing one coin. Runs the eight-frame flip animation with two `QTimer`s and ignores clicks while animating or after a win. |
| `mypushbutton.h/.cpp` | Image-based `QPushButton` with an optional pressed image and a small bounce animation used by the start button. |
| `dataconfig.h/.cpp` | Holds the 20 level layouts as 4×4 grids (`1` = face-up, `0` = face-down) in a `QMap<int, QVector<QVector<int>>>` keyed by level number. |
| `img.qrc`, `img/` | Qt resource file and the PNG/WAV assets it bundles. |
| `docs/` | Miscellaneous Qt notes (currently an example of re-implementing focus events on a `QLineEdit`). |

## Adding or editing levels

Level data lives in `dataconfig.cpp`. Each level is a `4x4` integer array that is copied into `mData` under its level number. To change a level, edit the corresponding array. To add a level beyond 20, add a new array and `mData.insert(n, v)` call, then increase the loop bound in `chooselevelscene.cpp` so a button is created for it.

## Acknowledgements

The game structure and artwork follow the classic "翻金币" (flip coins) Qt teaching project. Coin, board, button and background assets are in `img/`.
