// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QColor>
#include <QString>
#include <QVector>

class Bullet {
public:
    Bullet(int x, int y, int speed, QColor color);
    QRect getRect() const;
    QColor getColor() const;
    void setColor(const QColor &color);
    void move();
    void setPos(int x, int y);
    bool needMove();
    QVector<QVector<int>> getPattern() const; // Added function to retrieve pattern

private:
    QRect rect;
    int speed;
    QColor color;
    QVector<QVector<int>> pattern;
};

#endif // BULLET_H
