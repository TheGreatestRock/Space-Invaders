// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include "player.h"
#include "bullet.h"
#include "invader.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

signals:
    void goToMain();
    void goToMainWin();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();
    void start();

private:
    QTimer *timer;
    Player player;
    QList<Bullet*> bullets;
    bool leftPressed;
    bool rightPressed;
    QList<Invader*> invader;
};

#endif // GAMEWINDOW_H
