// The level picker: a grid of numbered buttons, one per level.
#ifndef COINFILP_CHOOSELEVELSCENE_H_
#define COINFILP_CHOOSELEVELSCENE_H_

#include <QMainWindow>
#include <QPixmap>

class QPaintEvent;
class QSoundEffect;

namespace coinfilp {

class PlayScene;

class ChooseLevelScene : public QMainWindow {
  Q_OBJECT

 public:
  explicit ChooseLevelScene(QWidget* parent = nullptr);

 signals:
  // Emitted when the user presses the back button.
  void BackRequested();

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CreateMenu();
  void CreateBackButton();
  void CreateLevelButtons();

  // Opens the play scene for `level` in place of this window.
  void OpenLevel(int level);

  // Returns from the play scene to this window and destroys the play scene.
  void OnPlaySceneBack();

  // The currently open play scene, or nullptr. It is a top-level window
  // without a Qt parent and is released with deleteLater() in
  // OnPlaySceneBack().
  PlayScene* play_scene_ = nullptr;
  QSoundEffect* back_sound_ = nullptr;
  QSoundEffect* choose_sound_ = nullptr;
  QPixmap background_;
  QPixmap title_;
};

}  // namespace coinfilp

#endif  // COINFILP_CHOOSELEVELSCENE_H_
