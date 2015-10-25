#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    Ui::Window *ui;
    void createActions();
    void createTrayIcon();

    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // WINDOW_H
