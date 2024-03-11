// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include "player.h"
#include "bullet.h"
#include "invader.h"


class GameWindow : public QWidget {
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void start();

signals:
    void goToMenu();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void updateGame();

private:
    QTimer* timer;
    bool leftPressed;
    bool rightPressed;
    bool spacePressed;
    Player player;
    Bullet bullet;
    Invader invader;
};

#endif // GAMEWINDOW_H
