#ifndef INVADER_H
#define INVADER_H

#include <QRect>
#include <QColor>
#include <QString>
#include <QVector>

class Invader {
public:
    Invader(int x, int y, double speed, QColor color);
    QRect getRect() const;
    QColor getColor() const;
    void setColor(QColor color);
    void move();
    void hitWall();
    void setSpeed(double speed);
    int getSpeed();
    void setDirection(int direction);
    int getDirection() const;
    void setPos(int x, int y);
    QVector<QVector<int>> getPattern() const;

private:
    QRect rect;
    int speed;
    int direction;
    QColor color;
    QVector<QVector<int>> pattern; // Store the invader pattern
};

#endif // INVADER_H
