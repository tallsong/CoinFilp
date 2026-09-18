#include "mainscene.h"

#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "chooselevelscene.h"
#include "constants.h"
#include "menus.h"
#include "mypushbutton.h"
#include "ui_mainscene.h"

namespace coinfilp {
namespace {

constexpr char kBackgroundImage[] = ":/img/PlayLevelSceneBg.png";
constexpr char kStartButtonImage[] = ":/img/MenuSceneStartButton.png";

}  // namespace

MainScene::MainScene(QWidget* parent)
    : QMainWindow(parent),
      ui_(std::make_unique<Ui::MainScene>()),
      choose_level_scene_(std::make_unique<ChooseLevelScene>()),
      background_(kBackgroundImage),
      title_(QPixmap(kTitleImage)
                 .scaled(QPixmap(kTitleImage).size() / 2, Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)) {
  ui_->setupUi(this);
  setWindowTitle("CoinFilp");
  setFixedSize(kSceneWidth, kSceneHeight);
  setWindowIcon(QIcon(kWindowIcon));

  SetUpQuitAction(ui_->actionquit);
  connect(choose_level_scene_.get(), &ChooseLevelScene::BackRequested, this,
          &MainScene::OnChooseLevelSceneBack);

  CreateStartButton();
}

MainScene::~MainScene() = default;

void MainScene::CreateStartButton() {
  auto* start_button = new MyPushButton(kStartButtonImage, QString(), this);
  start_button->move((width() - start_button->width()) / 2, height() * 7 / 10);
  connect(start_button, &QPushButton::clicked, this, [this, start_button] {
    start_button->Bounce();
    QTimer::singleShot(kSceneSwitchDelayMs, this,
                       &MainScene::ShowChooseLevelScene);
  });
}

void MainScene::ShowChooseLevelScene() {
  hide();
  choose_level_scene_->setGeometry(geometry());
  choose_level_scene_->show();
}

void MainScene::OnChooseLevelSceneBack() {
  QTimer::singleShot(kSceneSwitchDelayMs, this, [this] {
    choose_level_scene_->hide();
    setGeometry(choose_level_scene_->geometry());
    show();
  });
}

void MainScene::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.drawPixmap(0, 0, width(), height(), background_);
  painter.drawPixmap(10, 30, title_);
}

}  // namespace coinfilp
