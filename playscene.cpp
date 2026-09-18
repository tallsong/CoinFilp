#include "playscene.h"

#include <QAbstractAnimation>
#include <QAction>
#include <QDebug>
#include <QEasingCurve>
#include <QFont>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QRect>
#include <QSoundEffect>
#include <QTimer>
#include <QUrl>

#include "constants.h"
#include "mycoin.h"
#include "mypushbutton.h"

namespace coinfilp {
namespace {

constexpr char kBackgroundImage[] = ":/img/PlayLevelSceneBg.png";
constexpr char kBoardNodeImage[] = ":/img/BoardNode.png";
constexpr char kWinBannerImage[] = ":/img/LevelCompletedDialogBg.png";
constexpr char kFlipSound[] = "qrc:/img/ConFlipSound.wav";
constexpr char kWinSound[] = "qrc:/img/LevelWinSound.wav";

// Top-left corner of the board and the coin inset within each board node.
constexpr int kBoardLeft = 57;
constexpr int kBoardTop = 200;
constexpr int kCoinInsetX = 2;
constexpr int kCoinInsetY = 4;

// Neighbouring coins flip one animation frame after the clicked coin.
constexpr int kNeighbourFlipDelayMs = 30;

constexpr int kWinBannerDrop = 114;
constexpr int kWinBannerDurationMs = 1000;

}  // namespace

PlayScene::PlayScene(int level, QWidget* parent)
    : QMainWindow(parent),
      level_(level),
      background_(kBackgroundImage),
      title_(QPixmap(kTitleImage).scaled(QPixmap(kTitleImage).size() / 2)) {
  setFixedSize(kSceneWidth, kSceneHeight);
  setWindowIcon(QIcon(kWindowIcon));
  setWindowTitle("play scene");

  back_sound_ = new QSoundEffect(this);
  back_sound_->setSource(QUrl(kBackButtonSound));
  flip_sound_ = new QSoundEffect(this);
  flip_sound_->setSource(QUrl(kFlipSound));
  win_sound_ = new QSoundEffect(this);
  win_sound_->setSource(QUrl(kWinSound));

  CreateMenu();
  CreateBackButton();
  CreateLevelLabel();
  CreateWinBanner();
  CreateBoard();
}

void PlayScene::CreateMenu() {
  QMenu* start_menu = menuBar()->addMenu("start");
  QAction* quit_action = start_menu->addAction("quit");
  connect(quit_action, &QAction::triggered, this, &PlayScene::close);
}

void PlayScene::CreateBackButton() {
  auto* back_button =
      new MyPushButton(kBackButtonImage, kBackButtonPressedImage, this);
  back_button->move(width() - back_button->width(),
                    height() - back_button->height());
  connect(back_button, &QPushButton::clicked, this, [this] {
    back_sound_->play();
    QTimer::singleShot(kSceneSwitchDelayMs, this,
                       [this] { emit BackRequested(); });
  });
}

void PlayScene::CreateLevelLabel() {
  auto* label = new QLabel(QString("level: %1").arg(level_), this);
  QFont font;
  font.setFamily("华文新魏");
  font.setPointSize(20);
  label->setFont(font);
  label->setGeometry(QRect(30, height() - 50, 160, 50));
}

void PlayScene::CreateWinBanner() {
  const QPixmap banner(kWinBannerImage);
  win_banner_ = new QLabel(this);
  win_banner_->setPixmap(banner);
  // Parked above the window; ShowWin() animates it into view.
  win_banner_->setGeometry((width() - banner.width()) / 2, -banner.height(),
                           banner.width(), banner.height());
}

void PlayScene::CreateBoard() {
  const Board& board = GetLevelBoard(level_);
  const QPixmap node(kBoardNodeImage);

  for (int column = 0; column < kBoardSize; ++column) {
    for (int row = 0; row < kBoardSize; ++row) {
      const int x = kBoardLeft + column * node.width();
      const int y = kBoardTop + row * node.height();

      auto* node_label = new QLabel(this);
      node_label->setPixmap(node);
      node_label->setGeometry(x, y, node.width(), node.height());

      auto* coin = new MyCoin(board[column][row], this);
      coin->move(x + kCoinInsetX, y + kCoinInsetY);
      coins_[column][row] = coin;

      connect(coin, &MyCoin::clicked, this,
              [this, column, row] { OnCoinClicked(column, row); });
    }
  }
}

void PlayScene::OnCoinClicked(int column, int row) {
  flip_sound_->play();
  coins_[column][row]->Flip();

  QTimer::singleShot(kNeighbourFlipDelayMs, this, [this, column, row] {
    if (column > 0) coins_[column - 1][row]->Flip();
    if (column < kBoardSize - 1) coins_[column + 1][row]->Flip();
    if (row > 0) coins_[column][row - 1]->Flip();
    if (row < kBoardSize - 1) coins_[column][row + 1]->Flip();

    if (IsSolved()) {
      ShowWin();
    }
  });
}

bool PlayScene::IsSolved() const {
  for (const auto& column : coins_) {
    for (const MyCoin* coin : column) {
      if (!coin->face_up()) {
        return false;
      }
    }
  }
  return true;
}

void PlayScene::ShowWin() {
  for (auto& column : coins_) {
    for (MyCoin* coin : column) {
      coin->set_locked(true);
    }
  }
  win_sound_->play();

  auto* animation = new QPropertyAnimation(win_banner_, "geometry", this);
  animation->setDuration(kWinBannerDurationMs);
  animation->setStartValue(win_banner_->geometry());
  animation->setEndValue(win_banner_->geometry().translated(0, kWinBannerDrop));
  animation->setEasingCurve(QEasingCurve::OutBounce);
  animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, width(), height(), background_);
  painter.drawPixmap(10, 30, title_);
}

}  // namespace coinfilp
