// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include <QColor>

class Player {
public:
    Player(int x, int y, int width, int height, int speed, QColor color);

    QRect getRect() const;
    QRect getCannon() const;
    QColor getColor() const;
    void setColor(const QColor &color);

    void moveLeft();
    void moveRight();
    void setPos(int x, int y);

private:
    QRect rect;
    int speed;
    QColor color;
};

#endif // PLAYER_H
