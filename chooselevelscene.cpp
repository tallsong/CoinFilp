#include "chooselevelscene.h"

#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QSoundEffect>
#include <QString>
#include <QTimer>
#include <QUrl>

#include "constants.h"
#include "dataconfig.h"
#include "mypushbutton.h"
#include "playscene.h"

namespace coinfilp {
namespace {

constexpr char kBackgroundImage[] = ":/img/OtherSceneBg.png";
constexpr char kLevelIconImage[] = ":/img/LevelIcon.png";
constexpr char kChooseSound[] = "qrc:/img/TapButtonSound.wav";

// Layout of the level button grid.
constexpr int kGridColumns = 4;
constexpr int kGridLeft = 25;
constexpr int kGridTop = 130;
constexpr int kGridSpacing = 70;

}  // namespace

ChooseLevelScene::ChooseLevelScene(QWidget* parent)
    : QMainWindow(parent), background_(kBackgroundImage), title_(kTitleImage) {
  setWindowTitle("choose level scene");
  setFixedSize(kSceneWidth, kSceneHeight);
  setWindowIcon(QIcon(kWindowIcon));

  back_sound_ = new QSoundEffect(this);
  back_sound_->setSource(QUrl(kBackButtonSound));
  choose_sound_ = new QSoundEffect(this);
  choose_sound_->setSource(QUrl(kChooseSound));

  CreateMenu();
  CreateBackButton();
  CreateLevelButtons();
}

void ChooseLevelScene::CreateMenu() {
  QMenu* start_menu = menuBar()->addMenu("start");
  QAction* quit_action = start_menu->addAction("quit");
  connect(quit_action, &QAction::triggered, this, &ChooseLevelScene::close);
}

void ChooseLevelScene::CreateBackButton() {
  auto* back_button =
      new MyPushButton(kBackButtonImage, kBackButtonPressedImage, this);
  back_button->move(width() - back_button->width(),
                    height() - back_button->height());
  connect(back_button, &QPushButton::clicked, this, [this] {
    QTimer::singleShot(kSceneSwitchDelayMs, this, [this] {
      back_sound_->play();
      emit BackRequested();
    });
  });
}

void ChooseLevelScene::CreateLevelButtons() {
  for (int index = 0; index < kLevelCount; ++index) {
    const int level = index + 1;
    const int x = kGridLeft + (index % kGridColumns) * kGridSpacing;
    const int y = kGridTop + (index / kGridColumns) * kGridSpacing;

    auto* button = new MyPushButton(kLevelIconImage, QString(), this);
    button->move(x, y);
    connect(button, &QPushButton::clicked, this,
            [this, level] { OpenLevel(level); });

    auto* label = new QLabel(QString::number(level), this);
    label->setFixedSize(button->size());
    label->move(x, y);
    label->setAlignment(Qt::AlignCenter);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
  }
}

void ChooseLevelScene::OpenLevel(int level) {
  choose_sound_->play();
  play_scene_ = new PlayScene(level);
  connect(play_scene_, &PlayScene::BackRequested, this,
          &ChooseLevelScene::OnPlaySceneBack);
  hide();
  play_scene_->setGeometry(geometry());
  play_scene_->show();
}

void ChooseLevelScene::OnPlaySceneBack() {
  setGeometry(play_scene_->geometry());
  // The play scene is still emitting the signal that got us here, so defer
  // its destruction to the event loop.
  play_scene_->deleteLater();
  play_scene_ = nullptr;
  show();
}

void ChooseLevelScene::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, width(), height(), background_);
  painter.drawPixmap((width() - title_.width()) / 2, 30, title_);
}

}  // namespace coinfilp
