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
#include <QNetworkReply>

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
    QTimer* invaderShootTimer = new QTimer(this);

    Player *player;
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
    QColor powerupColor;
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

    void checkSaveFiles();

    void handleDownloadFinished(QNetworkReply* reply);
    void handleInvaderShoot();

    int PLAYER_SIZE = 5;
    int INVADER_SIZE = 5;
    int INVADER_SPACING = 45;
    int BULLET_SPEED = 12;
    int FIRE_RATE = 10;
    int SCORE_PER_INVADER = 10;
    int UPDATE_INTERVAL = 20;
    int INVADER_SHOOT_INTERVAL = 2000;

};

#endif // GAMEWINDOW_H
