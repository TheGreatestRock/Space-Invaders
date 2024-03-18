#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "titlewindow.h"
#include "gamewindow.h"
#include "menuwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TitleWindow *titleWindow;
    GameWindow *gameWindow;
    MenuWindow *menuWindow;
    bool gameWon;

    void createSaveFile();
    void goToMenu();
    void goToGame();
    void goToMain();
    void goToMainWin();

private slots:
    void handlePlayButtonClicked();
    void handleOptionsButtonClicked();
    void handleExitButtonClicked();
    void handleMainButtonClicked();
    void handleWin();
};
#endif // MAINWINDOW_H
