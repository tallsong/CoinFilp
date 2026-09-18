#include <QApplication>

#include "mainscene.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  coinfilp::MainScene main_scene;
  main_scene.show();
  return app.exec();
}
