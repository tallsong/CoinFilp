// An image-based push button with an optional pressed image and a bounce
// animation.
#ifndef COINFILP_MYPUSHBUTTON_H_
#define COINFILP_MYPUSHBUTTON_H_

#include <QPushButton>
#include <QString>

class QMouseEvent;

namespace coinfilp {

class MyPushButton : public QPushButton {
  Q_OBJECT

 public:
  // Shows `normal_image_path` and sizes the button to match it. If
  // `pressed_image_path` is not empty, that image is shown while the mouse
  // button is held down.
  explicit MyPushButton(const QString& normal_image_path,
                        const QString& pressed_image_path = QString(),
                        QWidget* parent = nullptr);

  // Dips the button down and springs it back to its original position.
  void Bounce();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

 private:
  // Loads `image_path` as the button icon and resizes the button to fit.
  void SetImage(const QString& image_path);

  QString normal_image_path_;
  QString pressed_image_path_;
};

}  // namespace coinfilp

#endif  // COINFILP_MYPUSHBUTTON_H_
