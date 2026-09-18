// The main menu window.
#ifndef COINFILP_MAINSCENE_H_
#define COINFILP_MAINSCENE_H_

#include <QMainWindow>
#include <QPixmap>
#include <memory>

class QPaintEvent;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

namespace coinfilp {

class ChooseLevelScene;

class MainScene : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainScene(QWidget* parent = nullptr);
  ~MainScene() override;

  MainScene(const MainScene&) = delete;
  MainScene& operator=(const MainScene&) = delete;

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CreateStartButton();

  // Swaps this window for the level picker, and back again.
  void ShowChooseLevelScene();
  void OnChooseLevelSceneBack();

  std::unique_ptr<Ui::MainScene> ui_;
  std::unique_ptr<ChooseLevelScene> choose_level_scene_;
  QPixmap background_;
  QPixmap title_;
};

}  // namespace coinfilp

#endif  // COINFILP_MAINSCENE_H_
