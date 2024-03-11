// Invader.cpp
#include "invader.h"

Invader::Invader(int x, int y, int width, int height, int speed, QColor color)
    : rect(x, y, width, height), speed(speed), direction(1), color(color) {}

QRect Invader::getRect() const {
    return rect;
}

QColor Invader::getColor() const {
    return color;
}

void Invader::setColor(QColor color) {
    this->color = color;
}

void Invader::move() {
    rect.moveLeft(rect.left() + speed * direction);
}

void Invader::hitWall() {
    rect.moveTop(rect.top() + 20);
    direction = -direction;
}

void Invader::setSpeed(int speed) {
    this->speed = speed;
}

void Invader::setDirection(int direction) {
    this->direction = direction;
}

int Invader::getDirection() const {
    return direction;
}

void Invader::setPos(int x, int y) {
    rect.moveTo(x, y);
}
