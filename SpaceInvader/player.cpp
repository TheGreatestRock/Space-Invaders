// Player.cpp
#include "player.h"

Player::Player(int x, int y, int width, int height, int speed)
    : rect(x, y, width, height), speed(speed) {}

QRect Player::getRect() const {
    return rect;
}

QRect Player::getCannon() const {
    return QRect(rect.left() + rect.width() / 2 - 2, rect.bottom() - 10, 4, 10);
}


void Player::moveLeft() {
    rect.moveLeft(rect.left() - speed);
}

void Player::moveRight() {
    rect.moveRight(rect.right() + speed);
}

void Player::setPos(int x, int y) {
    rect.moveTo(x, y);
}
