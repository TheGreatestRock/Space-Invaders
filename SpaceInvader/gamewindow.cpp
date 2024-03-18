// gamewindow.cpp
#include "gamewindow.h"
#include <QPainter>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent),
    player(width()/2, (9*height())/10, 20, 5, 5, Qt::white), score(0)
{
    qDebug() << "GameWindow constructor";
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(20); // Update game every 20 milliseconds
    qDebug() << timer->isActive();
    leftPressed = false;
    rightPressed = false;

    resetGame();
}

void GameWindow::loadOptionsFromFile() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
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

    // Reinitialize player position
    player.setPos(width()/2, (9 * height()) / 10);
    player.setColor(playerColor);

    // Reinitialize invader positions
    const int invaderSpacing = (width() - (10 * 10)) / (10 + 1);

    for (int i = 0; i < numberOfInvaders; ++i) {
        int row = i / 10; // Calculate the row
        int col = i % 10; // Calculate the column within the row

        int x = invaderSpacing + col * (10 + invaderSpacing); // Calculate x position
        int y = 50 + row * 20; // Calculate y position

        Invader* newInvader = new Invader(x, y, 10, 5, 5, invaderColor);
        invader.append(newInvader);
    }

    // Restart the game timer if it's not active
    if (!timer->isActive())
        timer->start(20);

    // Reset key presses
    leftPressed = false;
    rightPressed = false;

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
    currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    painter.drawText(width() - 100, 20, currentTime);

    // Draw player spaceship
    painter.setBrush(player.getColor());
    painter.drawRect(player.getRect());
    painter.drawRect(player.getCannon());

    // Draw bullets
    for (Bullet* bullet : bullets) {
        painter.setBrush(bullet->getColor());
        painter.drawRect(bullet->getRect());
    }

    // Draw invader
    for (Invader* invader : invader) {
        painter.setBrush(invader->getColor());
        painter.drawRect(invader->getRect());
    }
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
        // Create a new bullet and add it to the list
        Bullet* newBullet = new Bullet(player.getRect().x() + 10, player.getRect().y(), 5, 5, 5, bulletColor);
        bullets.append(newBullet);
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
    // Update bullets
    for (int i = 0; i < bullets.size(); ++i) {
        Bullet* bullet = bullets.at(i);
        bullet->move();
        // Check if bullet is out of bounds, delete it if so
        if (bullet->getRect().y() < 0) {
            delete bullet;
            bullets.removeAt(i);
            qDebug() << "Bullet deleted";
            continue; // Continue to the next iteration to avoid accessing removed element
        }
    }
    // Update invader position
    for (int i = 0; i < invader.size(); ++i) {
        Invader* inv = invader.at(i);
        inv->move();
        // Check if invader is out of bounds, change direction if so
        if (inv->getRect().right() > width() || inv->getRect().left() < 0) {
            inv->hitWall();
        }
    }
    //check bullet/invader collision
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
                    invader[k]->setSpeed(invader[k]->getSpeed()*1.1);
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
    if (rightPressed && player.getRect().right() < width()- player.getRect().width()/2){
        player.moveRight();
        qDebug() << "Player moved right";
    }

    // Check if invader list is empty
    if (invader.isEmpty()) {
        emit WinEvent();
        timer->stop();
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
    for (Invader* invader : invader) {
        delete invader;
    }
}
