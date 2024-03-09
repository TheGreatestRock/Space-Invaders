// Invader.cpp
#include "invader.h"

Invader::Invader(int x, int y, int width, int height, int speed)
    : rect(x, y, width, height), speed(speed), direction(1) {}

QRect Invader::getRect() const {
    return rect;
}

void Invader::move() {
    rect.moveLeft(rect.left() + speed * direction);
}

void Invader::setDirection(int direction) {
    this->direction = direction;
}

int Invader::getDirection() const {
    return direction;
}
