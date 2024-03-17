#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
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

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void goToMenu();
    void goToGame();
    void goToMain();
    void goToMainWin();
    void handlePlayButtonClicked();
    void handleOptionsButtonClicked();
    void handleExitButtonClicked();

private:
    Ui::MainWindow *ui;
    GameWindow *gameWindow;
    MenuWindow *menuWindow;
    bool gameWon;
};

#endif // MAINWINDOW_H
