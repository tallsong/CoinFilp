// Menu helpers shared by the scenes.
#ifndef COINFILP_MENUS_H_
#define COINFILP_MENUS_H_

class QAction;
class QMainWindow;

namespace coinfilp {

// Configures `quit_action` as the application's Quit command: it gets the
// platform Quit shortcut (Cmd+Q on macOS, where it also moves into the
// application menu) and quits the whole application rather than closing one
// window.
void SetUpQuitAction(QAction* quit_action);

// Adds the "start" menu with a Quit item to `window`.
void AddStartMenu(QMainWindow* window);

}  // namespace coinfilp

#endif  // COINFILP_MENUS_H_
