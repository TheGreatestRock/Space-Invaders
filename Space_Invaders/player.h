// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>

class Player {
public:
    Player(int x, int y, int width, int height, int speed);
    QRect getRect() const;
    QRect getCannon() const;
    void moveLeft();
    void moveRight();

private:
    QRect rect;
    int speed;
};

#endif // PLAYER_H
