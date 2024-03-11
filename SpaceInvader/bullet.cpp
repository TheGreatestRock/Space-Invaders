// Bullet.cpp
#include "bullet.h"

Bullet::Bullet(int x, int y, int width, int height, int speed, QColor color)
    : rect(x, y, width, height), speed(speed), color(color) {}

QRect Bullet::getRect() const {
    return rect;
}

QColor Bullet::getColor() const {
    return color;
}

void Bullet::setColor(const QColor &color) {
    this->color = color;
}

void Bullet::move() {
    rect.moveTop(rect.top() - speed);
}

void Bullet::setPos(int x, int y) {
    rect.moveTo(x, y);
}

bool Bullet::needMove() {
    return rect.top() > 0;
}

