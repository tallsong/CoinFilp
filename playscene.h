// The game board for one level.
#ifndef COINFILP_PLAYSCENE_H_
#define COINFILP_PLAYSCENE_H_

#include <QMainWindow>
#include <array>

#include "dataconfig.h"

class QLabel;
class QPaintEvent;
class QPixmap;
class QSoundEffect;

namespace coinfilp {

class MyCoin;

class PlayScene : public QMainWindow {
  Q_OBJECT

 public:
  explicit PlayScene(int level, QWidget* parent = nullptr);

  int level() const { return level_; }

 signals:
  // Emitted when the user presses the back button.
  void BackRequested();

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CreateMenu();
  void CreateBackButton();
  void CreateLevelLabel();
  void CreateWinBanner();
  void CreateBoard();

  // Handles a click on the coin at (`column`, `row`): flips it and its four
  // neighbours, then checks whether the level is solved.
  void OnCoinClicked(int column, int row);
  bool IsSolved() const;
  void ShowWin();

  int level_;
  std::array<std::array<MyCoin*, kBoardSize>, kBoardSize> coins_{};
  QLabel* win_banner_ = nullptr;
  QSoundEffect* back_sound_ = nullptr;
  QSoundEffect* flip_sound_ = nullptr;
  QSoundEffect* win_sound_ = nullptr;
  QPixmap background_;
  QPixmap title_;
};

}  // namespace coinfilp

#endif  // COINFILP_PLAYSCENE_H_
