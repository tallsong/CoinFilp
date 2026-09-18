#include "menus.h"

#include <QAction>
#include <QCoreApplication>
#include <QKeySequence>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

namespace coinfilp {

void SetUpQuitAction(QAction* quit_action) {
  quit_action->setMenuRole(QAction::QuitRole);
  quit_action->setShortcut(QKeySequence::Quit);
  QObject::connect(quit_action, &QAction::triggered, qApp,
                   &QCoreApplication::quit, Qt::QueuedConnection);
}

void AddStartMenu(QMainWindow* window) {
  QMenu* start_menu = window->menuBar()->addMenu("start");
  SetUpQuitAction(start_menu->addAction("quit"));
}

}  // namespace coinfilp
