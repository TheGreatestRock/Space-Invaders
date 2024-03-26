// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include <QColor>
#include <QString>

class Player {
public:
    Player(int x, int y, int speed, QColor color);
    QRect getRect() const;
    QRect getCannon() const;
    QColor getColor() const;
    void setColor(const QColor &color);
    void moveLeft();
    void moveRight();
    void setPos(int x, int y);
    QVector<QVector<int>> getPattern() const;


private:
    QRect rect;
    int speed;
    QColor color;
    QVector<QVector<int>> pattern;
};

#endif // PLAYER_H
