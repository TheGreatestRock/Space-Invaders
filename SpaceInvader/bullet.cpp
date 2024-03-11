// Bullet.cpp
#include "bullet.h"

Bullet::Bullet(int x, int y, int width, int height, int speed)
    : rect(x, y, width, height), speed(speed) {}

QRect Bullet::getRect() const {
    return rect;
}

void Bullet::move() {
    rect.moveTop(rect.top() - speed);
}

void Bullet::setPos(int x, int y) {
    rect.moveTo(x, y);
}
