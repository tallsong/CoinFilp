#include <QApplication>
#include <QIcon>

#include "constants.h"
#include "mainscene.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QApplication::setOrganizationName("tallsong");
  QApplication::setOrganizationDomain("tallsong.github.io");
  QApplication::setApplicationName("CoinFilp");
  QApplication::setApplicationDisplayName("CoinFilp");
  QApplication::setApplicationVersion("1.1.0");
  QApplication::setWindowIcon(QIcon(coinfilp::kWindowIcon));

  coinfilp::MainScene main_scene;
  main_scene.show();
  return app.exec();
}
