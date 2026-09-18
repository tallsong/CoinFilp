// Level layouts for the coin-flip puzzle.
#ifndef COINFILP_DATACONFIG_H_
#define COINFILP_DATACONFIG_H_

#include <array>

namespace coinfilp {

// Number of rows and columns on the board.
inline constexpr int kBoardSize = 4;

// Number of hand-authored levels.
inline constexpr int kLevelCount = 20;

// One board layout, indexed as board[column][row]. `true` means the coin
// starts face-up (gold); `false` means face-down (silver).
using Board = std::array<std::array<bool, kBoardSize>, kBoardSize>;

// Returns the initial layout of `level` (1-based). Out-of-range levels are
// clamped to the nearest valid level.
const Board& GetLevelBoard(int level);

}  // namespace coinfilp

#endif  // COINFILP_DATACONFIG_H_
