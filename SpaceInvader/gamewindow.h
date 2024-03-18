// gamewindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QColor>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QFileInfo>
#include <QDateTime>
#include "player.h"
#include "bullet.h"
#include "invader.h"
#include "shopwindow.h"


class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void resetGame();
    void start();

public slots:
    void handleCogButtonClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Player player;
    QList<Bullet*> bullets;
    QList<Invader*> invader;
    QTimer *timer;
    bool leftPressed;
    bool rightPressed;
    QColor playerColor;
    QColor bulletColor;
    QColor invaderColor;
    int numberOfInvaders;
    int score;
    QString currentTime;

    void loadOptionsFromFile();
    void updateGame();
    ShopWindow *shopWindow;
    QPushButton *cogButton;

signals:
    void MainButtonClicked();
    void WinEvent();
};

#endif // GAMEWINDOW_H
