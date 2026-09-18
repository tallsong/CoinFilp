// A single coin on the game board.
#ifndef COINFILP_MYCOIN_H_
#define COINFILP_MYCOIN_H_

#include <QPushButton>

class QMouseEvent;
class QTimer;

namespace coinfilp {

class MyCoin : public QPushButton {
  Q_OBJECT

 public:
  explicit MyCoin(bool face_up, QWidget* parent = nullptr);

  // Whether the coin currently shows (or is flipping to) its gold side.
  bool face_up() const { return face_up_; }

  // A locked coin ignores mouse presses. Used once a level has been solved.
  void set_locked(bool locked) { locked_ = locked; }

  // Turns the coin over, playing the eight-frame flip animation.
  void Flip();

 protected:
  void mousePressEvent(QMouseEvent* event) override;

 private:
  // Displays animation frame `frame`, in [kFirstFrame, kLastFrame].
  void ShowFrame(int frame);

  // Timer callback: shows the next frame and stops after the last one.
  void AdvanceAnimation();

  bool face_up_;
  bool locked_ = false;
  int frame_ = 0;
  int frame_step_ = 0;
  QTimer* animation_timer_;  // Owned by this widget through Qt parenting.
};

}  // namespace coinfilp

#endif  // COINFILP_MYCOIN_H_
