// Invader.h
#ifndef INVADER_H
#define INVADER_H

#include <QRect>
#include <QColor>

class Invader {
public:
    Invader(int x, int y, int width, int height, int speed, QColor color);
    QRect getRect() const;
    QColor getColor() const;
    void setColor(QColor color);
    void move();
    void setDirection(int direction);
    int getDirection() const;
    void setPos(int x, int y);
    void hitWall();
    void setSpeed(int speed);
private:
    QRect rect;
    QColor color;
    int speed;
    int direction;
};

#endif // INVADER_H
