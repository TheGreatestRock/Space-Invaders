// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QRect>

class Bullet {
public:
    Bullet(int x, int y, int width, int height, int speed);
    QRect getRect() const;
    void move();
    void setPos(int x, int y);
private:
    QRect rect;
    int speed;
};

#endif // BULLET_H