// Player.cpp
#include "player.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>
#include <QString>


Player::Player(int x, int y, int speed, QColor color)
    : speed(speed), color(color) {
    // Read pattern from file
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Ship";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QVector<QVector<int>> tempPattern; // Temporary storage for the pattern
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
        // Crop the pattern
        int top = 0, bottom = tempPattern.size() - 1;
        int left = 0, right = tempPattern[0].size() - 1;
        // Find top
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
        // Find bottom
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
        // Find left
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
        // Find right
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
        // Copy the cropped portion to pattern
        pattern.clear();
        for (int i = top; i <= bottom; ++i) {
            QVector<int> croppedRow;
            for (int j = left; j <= right; ++j) {
                croppedRow.push_back(tempPattern[i][j]);
            }
            pattern.push_back(croppedRow);
        }
    }
    //print the pattern wiut QDebug and
    for (int i = 0; i < pattern.size(); ++i) {
        QString sb;
        for (int j = 0; j < pattern.at(i).size(); ++j) {
            sb.append(QString::number(pattern.at(i).at(j)));
        }
        qDebug() << sb;
    }
    // Adjust rectangle size to fit the pattern
    int minWidth = pattern[0].size();
    int minHeight = pattern.size();
    rect = QRect(x, y, minWidth, minHeight);
}

QRect Player::getRect() const {
    return rect;
}

QRect Player::getCannon() const {
    //center of the player
    int x = rect.left() + rect.width() /2;
    int y = rect.top();
    return QRect(x, y, 1, 1);
}

QColor Player::getColor() const {
    return color;
}

void Player::setColor(const QColor &color) {
    this->color = color;
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

QVector<QVector<int>> Player::getPattern() const {
    return pattern;
}
