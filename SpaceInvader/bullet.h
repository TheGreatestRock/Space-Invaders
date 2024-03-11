// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QColor>

class Bullet {
public:
    Bullet(int x, int y, int width, int height, int speed, QColor color);
    QRect getRect() const;
    QColor getColor() const;
    void setColor(const QColor &color);

    void move();
    void setPos(int x, int y);
    bool needMove();
private:
    QRect rect;
    int speed;
    QColor color;
    
};

#endif // BULLET_H
