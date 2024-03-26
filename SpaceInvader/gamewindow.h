#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include "player.h"
#include "bullet.h"
#include "invader.h"
#include "winwindow.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void start();

signals:
    void MainButtonClicked();
    void WinEvent(int score);
    void LoseEvent(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

public slots:
    void resetGame();

private:
    QTimer *timer;
    Player player;
    QVector<Bullet*> bullets;
    QVector<Invader*> invader;
    WinWindow *winWindow;
    QColor playerColor;
    QColor bulletColor;
    QColor invaderColor;
    int score;
    bool leftPressed;
    bool rightPressed;
    int firerate;
    int numberOfInvaders;
    QColor inverted(const QColor& color);
    void loadOptionsFromFile();
};

#endif // GAMEWINDOW_H
