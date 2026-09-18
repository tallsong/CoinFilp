#include "mycoin.h"

#include <QDebug>
#include <QIcon>
#include <QMouseEvent>
#include <QPixmap>
#include <QString>
#include <QTimer>

namespace coinfilp {
namespace {

// Frames are named Coin0001.png (fully face-up) through Coin0008.png (fully
// face-down).
constexpr int kFirstFrame = 1;
constexpr int kLastFrame = 8;
constexpr int kFrameIntervalMs = 30;

QString FramePath(int frame) {
  return QString(":/img/Coin%1.png").arg(frame, 4, 10, QLatin1Char('0'));
}

}  // namespace

MyCoin::MyCoin(bool face_up, QWidget* parent)
    : QPushButton(parent),
      face_up_(face_up),
      animation_timer_(new QTimer(this)) {
  setStyleSheet("QPushButton{border:0px;}");
  ShowFrame(face_up_ ? kFirstFrame : kLastFrame);
  animation_timer_->setInterval(kFrameIntervalMs);
  connect(animation_timer_, &QTimer::timeout, this, &MyCoin::AdvanceAnimation);
}

void MyCoin::Flip() {
  face_up_ = !face_up_;
  // Flipping face-down runs through the frames forwards; flipping face-up
  // runs through them backwards.
  frame_step_ = face_up_ ? -1 : 1;
  frame_ = face_up_ ? kLastFrame : kFirstFrame;
  animation_timer_->start();
}

void MyCoin::mousePressEvent(QMouseEvent* event) {
  if (locked_ || animation_timer_->isActive()) {
    return;
  }
  QPushButton::mousePressEvent(event);
}

void MyCoin::ShowFrame(int frame) {
  const QString path = FramePath(frame);
  QPixmap pixmap;
  if (!pixmap.load(path)) {
    qWarning() << "MyCoin: failed to load frame" << path;
    return;
  }
  setFixedSize(pixmap.size());
  setIcon(QIcon(pixmap));
  setIconSize(pixmap.size());
}

void MyCoin::AdvanceAnimation() {
  ShowFrame(frame_);
  frame_ += frame_step_;
  if (frame_ < kFirstFrame || frame_ > kLastFrame) {
    animation_timer_->stop();
  }
}

}  // namespace coinfilp
