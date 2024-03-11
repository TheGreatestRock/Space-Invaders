// GameWindow.cpp
#include "gamewindow.h"
#include <QPainter>
#include <QDebug>


GameWindow::GameWindow(QWidget *parent) : QWidget(parent),
    player(window()->height()/1.5, window()->width()/1.5, 20, 5, 5, Qt::white)
{
    qDebug() << "GameWindow constructor";
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(20); // Update game every 20 milliseconds
    qDebug() << timer->isActive();
    leftPressed = false;
    rightPressed = false;

    // Initialize the invader list
    for (int i = 0; i < 2; ++i) {
        Invader* newInvader = new Invader(0, 0, 10, 5, 5, Qt::green);
        invader.append(newInvader);
    }
}


GameWindow::~GameWindow() {
    // Clean up bullets
    qDeleteAll(bullets);
    bullets.clear();
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black); // Background
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
        Bullet* newBullet = new Bullet(player.getRect().x() + 10, player.getRect().y(), 5, 5, 5, Qt::white);
        bullets.append(newBullet);
    }
    if (event->key() == Qt::Key_Escape) {
        emit goToMenu();
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
        }
    }
    // Update player position based on key presses
    if (leftPressed){
        if (player.getRect().left() > 0)
            player.moveLeft();
        qDebug() << "Player moved left";
    }
    if (rightPressed){
        if (player.getRect().right() < width()- player.getRect().width()/2)
            player.moveRight();
        qDebug() << "Player moved right";
    }
    // Update invader position
    for (Invader* invader : invader) {
        invader->move();
        // Check if invader is out of bounds, change direction if so
        if (invader->getRect().right() > width() || invader->getRect().left() < 0) {
            invader->hitWall();
        }
    }
    //check bullet/invader collision
    if (!bullets.isEmpty()) {
        for (int i = 0; i < bullets.size(); ++i) {
            for (int j = 0; j < invader.size(); ++j) {
                if (bullets.at(i)->getRect().intersects(invader.at(j)->getRect())) {
                    delete bullets.at(i);
                    bullets.removeAt(i);
                    delete invader.at(j);
                    invader.removeAt(j);
                    qDebug() << "Bullet and invader deleted";
                }
            }
        }
    }
    if (invader.isEmpty()) {
        emit goToMenuWin();
        timer->stop();
    }
    // Update the window
    update();
}

void GameWindow::start() {
    // Set initial player position
    player.setPos(200, 250);

    // Set initial invader position (if necessary)
    for (int i = 0; i < invader.size(); ++i) {
        invader.at(i)->setPos(50 + 50 * i, 50 + 20 * i);
    }

    // Start the game timer
    if (!timer->isActive())
        timer->start(20); // Update game every 20 milliseconds

    // Reset key presses
    leftPressed = false;
    rightPressed = false;
}
