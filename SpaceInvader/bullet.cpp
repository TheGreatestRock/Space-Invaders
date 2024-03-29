#include "bullet.h"

Bullet::Bullet(int x, int y, int speed, QColor color, bool isFromShip, bool isPowerUp)
    : speed(speed), color(color), isFromShip(isFromShip), isPowerUp(isPowerUp) {
    QString filePath;
    if (isPowerUp) {
        filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Powerup";
    } else {
        filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Bullet";
    }
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QVector<QVector<int>> tempPattern;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QVector<int> row;
            for (int i = 0; i < line.length(); ++i) {
                if (line.at(i) == '1')
                    row.push_back(1);
                else
                    row.push_back(0);
            }
            tempPattern.push_back(row);
        }
        file.close();

        int top = 0, bottom = tempPattern.size() - 1;
        int left = 0, right = tempPattern[0].size() - 1;

        while (top <= bottom) {
            bool allZero = true;
            for (int i = 0; i < tempPattern[top].size(); ++i) {
                if (tempPattern[top][i] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (!allZero)
                break;
            ++top;
        }

        while (bottom >= top) {
            bool allZero = true;
            for (int i = 0; i < tempPattern[bottom].size(); ++i) {
                if (tempPattern[bottom][i] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (!allZero)
                break;
            --bottom;
        }

        while (left <= right) {
            bool allZero = true;
            for (int i = top; i <= bottom; ++i) {
                if (tempPattern[i][left] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (!allZero)
                break;
            ++left;
        }

        while (right >= left) {
            bool allZero = true;
            for (int i = top; i <= bottom; ++i) {
                if (tempPattern[i][right] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (!allZero)
                break;
            --right;
        }

        pattern.clear();
        for (int i = top; i <= bottom; ++i) {
            QVector<int> croppedRow;
            for (int j = left; j <= right; ++j) {
                croppedRow.push_back(tempPattern[i][j]);
            }
            pattern.push_back(croppedRow);
        }

    }

    for (int i = 0; i < pattern.size(); ++i) {
        QString sb;
        for (int j = 0; j < pattern.at(i).size(); ++j) {
            sb.append(QString::number(pattern.at(i).at(j)));
        }
        qDebug() << sb;
    }

    int minWidth = pattern[0].size();
    int minHeight = pattern.size();
    rect = QRect(x, y, minWidth, minHeight);

    rect.moveLeft(x - minWidth / 2);
    rect.moveTop(y - minHeight / 2);
}

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
    if (isFromShip) {
        rect.moveTop(rect.top() - speed);
    } else {
        rect.moveTop(rect.top() + speed);
    }
}

void Bullet::setPos(int x, int y) {
    rect.moveTo(x, y);
}

bool Bullet::needMove() const {
    return rect.top() > 0;
}

QVector<QVector<int>> Bullet::getPattern() const {
    return pattern;
}

bool Bullet::getIsPowerUp() const {
    return isPowerUp;
}

bool Bullet::getIsShipBullet() const {
    return isFromShip;
}

void Bullet::setIsShipBullet(bool value) {
    isFromShip = value;;
}

void Bullet::setIsPowerUp(bool value) {
    isPowerUp = value;
}
