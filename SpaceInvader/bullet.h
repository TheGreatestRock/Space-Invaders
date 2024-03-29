#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QColor>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

class Bullet {
private:
    int speed;
    QColor color;
    QRect rect;
    QVector<QVector<int>> pattern;
    bool isFromShip;
    bool isPowerUp;

public:
    Bullet(int x, int y, int speed, QColor color, bool isFromShip, bool isPowerUp);

    QRect getRect() const;
    QColor getColor() const;
    void setColor(const QColor &color);
    void move();
    void setPos(int x, int y);
    bool needMove() const;
    QVector<QVector<int>> getPattern() const;
    bool getIsPowerUp() const;
    void setIsPowerUp(bool value);
    bool getIsShipBullet() const;
    void setIsShipBullet(bool value);
};

#endif // BULLET_H
