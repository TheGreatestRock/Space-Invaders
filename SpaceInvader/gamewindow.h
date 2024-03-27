#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include "player.h"
#include "bullet.h"
#include "invader.h"
#include "winwindow.h"
#include <QSoundEffect>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    Q_SIGNAL void MainButtonClicked();
    Q_SIGNAL void WinEvent(int score);
    Q_SIGNAL void LoseEvent(int score);

    void resetGame();


public slots:
    void start();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QTimer *timer;
    Player player;
    QVector<Bullet*> bullets;
    QVector<Invader*> invader;
    WinWindow *winWindow;
    bool leftPressed;
    bool rightPressed;
    int score;
    int firerate;
    int invaderMoveTimer;
    QColor playerColor;
    QColor bulletColor;
    QColor invaderColor;
    int numberOfInvaders;
    QSoundEffect *laserShootSound;
    QSoundEffect *explosionInvaderSound;
    QSoundEffect *explosionPlayerSound;

    void loadOptionsFromFile();
    void clearBulletsAndInvaders();
    void initializePlayerAndInvaders();
    void restartTimerIfNotActive();
    void resetKeyPresses();
    void resetGameParameters();
    void initializeSounds();
    QColor inverted(const QColor& color);
    void updateGame();
};

#endif // GAMEWINDOW_H
