#include "gamewindow.h"
#include <QPainter>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent),
    player(width()/2, (9*height())/10, 5, Qt::white), score(0)
{
    qDebug() << "GameWindow constructor";
    timer = new QTimer(this);
    winWindow =  new WinWindow(this, false);
    winWindow->hide();
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    connect(this, &GameWindow::WinEvent, winWindow, &WinWindow::setScore);
    connect(this, &GameWindow::LoseEvent, winWindow, &WinWindow::setScore);
    timer->start(20); // Update game every 20 milliseconds
    qDebug() << timer->isActive();
    leftPressed = false;
    rightPressed = false;
    resetGame();
}

void GameWindow::loadOptionsFromFile() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(filePath);
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(":");
            if (fields.length() == 2) {
                QString key = fields[0].trimmed();
                QString value = fields[1].trimmed();
                if (key == "ShipColor") {
                    playerColor = QColor(value);
                    qDebug() << "ShipColor: " << value << " converted to: " << playerColor;
                }
                else if (key == "BulletColor") {
                    bulletColor = QColor(value);
                    qDebug() << "BulletColor: " << value << " converted to: " << bulletColor;
                }
                else if (key == "InvaderColor") {
                    invaderColor = QColor(value);
                    qDebug() << "InvaderColor: " << value << " converted to: " << invaderColor;
                }
                else if (key == "NumberOfInvaders") {
                    numberOfInvaders = value.toInt();
                    qDebug() << "NumberOfInvaders: " << value << " converted to: " << numberOfInvaders;
                }
            }
        }
        file.close();
    }
    else {
        qDebug() << "Could not open file";
    }
}

void GameWindow::resetGame() {
    loadOptionsFromFile();
    // Clear bullets
    qDeleteAll(bullets);
    bullets.clear();

    // Clear invaders
    qDeleteAll(invader);
    invader.clear();

    // Reinitialize player position, look and color
    player = Player(width()/2, (9*height())/10, 5, playerColor);

    // Reinitialize invader positions , look abd color
    const int invaderSpacing = (width() - (10 * 10)) / (10 + 1);

    for (int i = 0; i < numberOfInvaders; ++i) {
        int row = i / 10; // Calculate the row
        int col = i % 10; // Calculate the column within the row

        int x = invaderSpacing + col * (10 + invaderSpacing); // Calculate x position
        int y = 50 + row * 20; // Calculate y position
        invader.append(new Invader(x, y, 5, invaderColor));
    }

    // Restart the game timer if it's not active
    if (!timer->isActive())
        timer->start(20);

    // Reset key presses
    leftPressed = false;
    rightPressed = false;

    score = 0;

    firerate = 0;

    update();
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black); // Background

    // Draw score at the top left
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, "Score: " + QString::number(score));

    // Draw clock with current time on the right
    QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    painter.drawText(width() - 100, 20, currentTime);

    //reset pen
    painter.setPen(Qt::black);
    // Draw player spaceship
    painter.setBrush(player.getColor());
    QVector<QVector<int>> playerPattern = player.getPattern();
    for (int i = 0; i < playerPattern.size(); ++i) {
        for (int j = 0; j < playerPattern.at(i).size(); ++j) {
            if (playerPattern.at(i).at(j) == 1) {
                painter.drawRect(player.getRect().left() + j, player.getRect().top() + i * 2, 2, 2);
            }
        }
    }

    // Draw bullets
    for (Bullet* bullet : bullets) {
        painter.setBrush(inverted(bullet->getColor()));
        QVector<QVector<int>> bulletPattern = bullet->getPattern();
        for (int i = 0; i < bulletPattern.size(); ++i) {
            for (int j = 0; j < bulletPattern.at(i).size(); ++j) {
                if (bulletPattern.at(i).at(j) == 1) {
                    painter.drawRect(bullet->getRect().left() + j, bullet->getRect().top() + i * 2, 2, 2);
                }
            }
        }
    }

    // Draw invaders
    for (Invader* invad : invader) {
        QVector<QVector<int>> pattern = invad->getPattern();
        //pattern is for 1 invader and each 1 is a pixel of the color of the invader, each pixel is 4x4
        for (int i = 0; i < pattern.size(); ++i) {
            for (int j = 0; j < pattern.at(i).size(); ++j) {
                if (pattern.at(i).at(j) == 1) {
                    painter.setBrush(invad->getColor());
                    painter.drawRect(invad->getRect().left() + j, invad->getRect().top() + i * 2, 2, 2);
                }
            }
        }
    }
}

QColor GameWindow::inverted(const QColor& color) {
    int red = 255 - color.red();
    int green = 255 - color.green();
    int blue = 255 - color.blue();

    return QColor(red, green, blue);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed: " << event->key();
    if (event->key() == Qt::Key_Left){
        leftPressed = true;
        qDebug() << "Left";
    }
    else if (event->key() == Qt::Key_Right){
        rightPressed = true;
        qDebug() << "Right";
    }
    else if (event->key() == Qt::Key_Space){
        qDebug() << "Space";
        if (firerate == 0){
            Bullet* newBullet = new Bullet(player.getCannon().left() + player.getCannon().width()/2, player.getCannon().top(), 12, bulletColor);
            bullets.append(newBullet);
            firerate = 0;
        } else {
            qDebug() << "cannot shoot " << firerate;
        }
    }
    if (event->key() == Qt::Key_Escape) {
        emit MainButtonClicked();
        qDebug() << "Escape";
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Key released: " << event->key();
    if (event->key() == Qt::Key_Left){
        leftPressed = false;
        qDebug() << "Left";
    }
    else if (event->key() == Qt::Key_Right){
        qDebug() << "Right";
        rightPressed = false;
    }
    if (event->key() == Qt::Key_Escape) {
        qDebug() << "Escape";
    }
}

void GameWindow::updateGame() {
    //decrease firerate
    if (firerate > 0){
        firerate--;
    }
    // Update bullets
    for (int i = 0; i < bullets.size(); ++i) {
        Bullet* bullet = bullets.at(i);
        bullet->move();
    // Check if bullet is out
        // Check if bullet is out of bounds, delete it if so
        if (bullet->getRect().y() < 0) {
            delete bullet;
            bullets.removeAt(i);
            qDebug() << "Bullet deleted";
            continue; // Continue to the next iteration to avoid accessing removed element
        }
    }
    // Update invaders position
    for (int i = 0; i < invader.size(); ++i) {
        Invader* invad = invader.at(i);
        invad->move();
        // Check if invader is out of bounds, change direction if so
        if (invad->getRect().right() > width() || invad->getRect().left() < 0) {
            invad->hitWall();
        }
        // Check if invader is at the same level as the player then emit LoseEvent
        if (invad->getRect().bottom() > player.getRect().top()) {
            winWindow->setWin(false);
            emit LoseEvent(score);
            timer->stop();
            winWindow->show();
        }
    }
    // Check bullet/invader collision
    for (int i = 0; i < bullets.size(); ++i) {
        for (int j = 0; j < invader.size(); ++j) {
            if (i >= bullets.size() || j >= invader.size()) {
                qDebug() << "Index out of range in bullet/invader collision check";
                break; // Break out of inner loop
            }
            if (bullets.at(i)->getRect().intersects(invader.at(j)->getRect())) {
                delete bullets.at(i);
                bullets.removeAt(i);
                delete invader.at(j);
                invader.removeAt(j);
                qDebug() << "Bullet and invader deleted";
                for (int k = 0; k < invader.size(); ++k) {
                    if (k >= invader.size()) {
                        qDebug() << "Index out of range in invader speed increment";
                        break;
                    }
                    invader[k]->setSpeed(invader[k]->getSpeed() * 1.1);
                }
                score += 10;
            }
        }
    }

    // Update player position based on key presses
    if (leftPressed && player.getRect().left() > 0){
        player.moveLeft();
        qDebug() << "Player moved left";
    }
    if (rightPressed && player.getRect().right() < width() - player.getRect().width()/2){
        player.moveRight();
        qDebug() << "Player moved right";
    }

    // Check if invaders list is empty
    if (invader.isEmpty()) {
        winWindow->setWin(true);
        emit WinEvent(score);
        timer->stop();
        winWindow->show();
    }

    // Update the window
    update();
}

void GameWindow::start() {
    resetGame();
    update();
}

GameWindow::~GameWindow() {
    delete timer;
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    for (Invader* inv : invader) {
        delete inv;
    }
}
