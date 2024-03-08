// Invader.h
#ifndef INVADER_H
#define INVADER_H

#include <QRect>

class Invader {
public:
    Invader(int x, int y, int width, int height, int speed);
    QRect getRect() const;
    void move();
    void setDirection(int direction);
    int getDirection() const;

private:
    QRect rect;
    int speed;
    int direction; // 1 for right, -1 for left
};

#endif // INVADER_H
