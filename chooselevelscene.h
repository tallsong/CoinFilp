// The level picker: a paged grid of numbered buttons, one per level.
#ifndef COINFILP_CHOOSELEVELSCENE_H_
#define COINFILP_CHOOSELEVELSCENE_H_

#include <QMainWindow>
#include <QPixmap>
#include <array>

class QLabel;
class QPaintEvent;
class QSoundEffect;

namespace coinfilp {

class MyPushButton;
class PlayScene;

class ChooseLevelScene : public QMainWindow {
  Q_OBJECT

 public:
  // Levels are shown kLevelsPerPage at a time.
  static constexpr int kGridColumns = 4;
  static constexpr int kGridRows = 5;
  static constexpr int kLevelsPerPage = kGridColumns * kGridRows;

  explicit ChooseLevelScene(QWidget* parent = nullptr);

  int page() const { return page_; }
  int page_count() const;

  // Shows page `page` (0-based); out-of-range pages wrap around.
  void SetPage(int page);

 signals:
  // Emitted when the user presses the back button.
  void BackRequested();

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CreateMenu();
  void CreateBackButton();
  void CreateLevelButtons();
  void CreatePageControls();

  // Adds an icon button at (`x`, `y`) with `text` drawn over it. Returns the
  // button and stores the overlay label in `*label`.
  MyPushButton* AddIconButton(int x, int y, const QString& text,
                              QLabel** label);

  // Opens the play scene for `level` in place of this window.
  void OpenLevel(int level);

  // Returns from the play scene to this window and destroys the play scene.
  void OnPlaySceneBack();

  int page_ = 0;
  std::array<MyPushButton*, kLevelsPerPage> level_buttons_{};
  std::array<QLabel*, kLevelsPerPage> level_labels_{};
  QLabel* page_label_ = nullptr;

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
