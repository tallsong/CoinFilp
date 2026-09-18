#include "mypushbutton.h"

#include <QAbstractAnimation>
#include <QDebug>
#include <QEasingCurve>
#include <QIcon>
#include <QMouseEvent>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QRect>
#include <QSequentialAnimationGroup>

namespace coinfilp {
namespace {

constexpr int kBounceDistance = 10;
constexpr int kBounceHalfDurationMs = 200;

}  // namespace

MyPushButton::MyPushButton(const QString& normal_image_path,
                           const QString& pressed_image_path, QWidget* parent)
    : QPushButton(parent),
      normal_image_path_(normal_image_path),
      pressed_image_path_(pressed_image_path) {
  setStyleSheet("QPushButton{border:0px;}");
  SetImage(normal_image_path_);
}

void MyPushButton::Bounce() {
  const QRect origin = geometry();
  const QRect lowered = origin.translated(0, kBounceDistance);

  auto* down = new QPropertyAnimation(this, "geometry");
  down->setDuration(kBounceHalfDurationMs);
  down->setStartValue(origin);
  down->setEndValue(lowered);
  down->setEasingCurve(QEasingCurve::OutBounce);

  auto* up = new QPropertyAnimation(this, "geometry");
  up->setDuration(kBounceHalfDurationMs);
  up->setStartValue(lowered);
  up->setEndValue(origin);
  up->setEasingCurve(QEasingCurve::OutBounce);

  auto* group = new QSequentialAnimationGroup(this);
  group->addAnimation(down);
  group->addAnimation(up);
  group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent* event) {
  if (!pressed_image_path_.isEmpty()) {
    SetImage(pressed_image_path_);
  }
  QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* event) {
  if (!pressed_image_path_.isEmpty()) {
    SetImage(normal_image_path_);
  }
  QPushButton::mouseReleaseEvent(event);
}

void MyPushButton::SetImage(const QString& image_path) {
  QPixmap pixmap;
  if (!pixmap.load(image_path)) {
    qWarning() << "MyPushButton: failed to load image" << image_path;
    return;
  }
  setFixedSize(pixmap.size());
  setIcon(QIcon(pixmap));
  setIconSize(pixmap.size());
}

}  // namespace coinfilp
