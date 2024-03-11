#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "menuwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayButtonClicked();
    void handleOptionsButtonClicked();
    void handleExitButtonClicked();
    void goToMenu();
    void goToGame();
    void goToMenuWin();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    GameWindow *gameWindow;
    MenuWindow *menuWindow;
};

#endif // MAINWINDOW_H
