#include "chooselevelscene.h"

#include <QFont>
#include <QIcon>
#include <QLabel>
#include <QPainter>
#include <QSoundEffect>
#include <QString>
#include <QTimer>
#include <QUrl>

#include "constants.h"
#include "dataconfig.h"
#include "menus.h"
#include "mypushbutton.h"
#include "playscene.h"

namespace coinfilp {
namespace {

constexpr char kBackgroundImage[] = ":/img/OtherSceneBg.png";
constexpr char kLevelIconImage[] = ":/img/LevelIcon.png";
constexpr char kChooseSound[] = "qrc:/img/TapButtonSound.wav";

// Layout of the level button grid.
constexpr int kGridLeft = 25;
constexpr int kGridTop = 130;
constexpr int kGridSpacing = 70;

// The page controls sit in a row below the grid.
constexpr int kPageControlsTop =
    kGridTop + ChooseLevelScene::kGridRows * kGridSpacing + 5;
constexpr int kPrevButtonLeft = kGridLeft;
constexpr int kNextButtonLeft =
    kGridLeft + (ChooseLevelScene::kGridColumns - 1) * kGridSpacing;

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
  CreatePageControls();
  SetPage(0);
}

int ChooseLevelScene::page_count() const {
  return (kLevelCount + kLevelsPerPage - 1) / kLevelsPerPage;
}

void ChooseLevelScene::SetPage(int page) {
  const int count = page_count();
  page_ = ((page % count) + count) % count;

  for (int index = 0; index < kLevelsPerPage; ++index) {
    const int level = page_ * kLevelsPerPage + index + 1;
    const bool exists = level <= kLevelCount;
    level_buttons_[index]->setVisible(exists);
    level_labels_[index]->setVisible(exists);
    level_labels_[index]->setText(QString::number(level));
  }
  page_label_->setText(QString("%1 / %2").arg(page_ + 1).arg(count));
}

void ChooseLevelScene::CreateMenu() { AddStartMenu(this); }

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
  for (int index = 0; index < kLevelsPerPage; ++index) {
    const int x = kGridLeft + (index % kGridColumns) * kGridSpacing;
    const int y = kGridTop + (index / kGridColumns) * kGridSpacing;
    level_buttons_[index] =
        AddIconButton(x, y, QString(), &level_labels_[index]);
    connect(level_buttons_[index], &QPushButton::clicked, this,
            [this, index] { OpenLevel(page_ * kLevelsPerPage + index + 1); });
  }
}

void ChooseLevelScene::CreatePageControls() {
  QLabel* unused = nullptr;
  MyPushButton* prev_button =
      AddIconButton(kPrevButtonLeft, kPageControlsTop, "<", &unused);
  MyPushButton* next_button =
      AddIconButton(kNextButtonLeft, kPageControlsTop, ">", &unused);
  connect(prev_button, &QPushButton::clicked, this, [this] {
    choose_sound_->play();
    SetPage(page_ - 1);
  });
  connect(next_button, &QPushButton::clicked, this, [this] {
    choose_sound_->play();
    SetPage(page_ + 1);
  });

  page_label_ = new QLabel(this);
  page_label_->setGeometry(prev_button->geometry().right(), kPageControlsTop,
                           next_button->x() - prev_button->geometry().right(),
                           prev_button->height());
  page_label_->setAlignment(Qt::AlignCenter);
  QFont font = page_label_->font();
  font.setPointSize(16);
  page_label_->setFont(font);
}

MyPushButton* ChooseLevelScene::AddIconButton(int x, int y, const QString& text,
                                              QLabel** label) {
  auto* button = new MyPushButton(kLevelIconImage, QString(), this);
  button->move(x, y);

  *label = new QLabel(text, this);
  (*label)->setFixedSize(button->size());
  (*label)->move(x, y);
  (*label)->setAlignment(Qt::AlignCenter);
  (*label)->setAttribute(Qt::WA_TransparentForMouseEvents);
  return button;
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
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.drawPixmap(0, 0, width(), height(), background_);
  painter.drawPixmap((width() - title_.width()) / 2, 30, title_);
}

}  // namespace coinfilp
