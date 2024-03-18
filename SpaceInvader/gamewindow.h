// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QStandardPaths>
#include <QDir>
#include "player.h"
#include "bullet.h"
#include "invader.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void resetGame();

signals:
    void MainButtonClicked();
    void WinEvent();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();
    void start();

private:
    QColor playerColor;
    int playerX;
    int playerY;
    QColor invaderColor;
    int numberOfInvaders;
    QColor bulletColor;

    QTimer *timer;
    Player player;
    QList<Bullet*> bullets;
    bool leftPressed;
    bool rightPressed;
    QList<Invader*> invader;
    void loadOptionsFromFile();
};

#endif // GAMEWINDOW_H
