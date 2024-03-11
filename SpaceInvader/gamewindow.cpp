// GameWindow.cpp
#include "gamewindow.h"
#include <QPainter>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent),
    player(window()->height()/1.5, window()->width()/1.5, 20, 5, 5),
    bullet(0, 0, 5, 5, 5),
    invader(0, 0, 20, 20, 5)
{
    qDebug() << "GameWindow constructor";
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(20); // Update game every 20 milliseconds
    leftPressed = false;
    rightPressed = false;
    spacePressed = false;
}

GameWindow::~GameWindow() {}

void GameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black); // Background
    painter.setPen(Qt::white);
    painter.drawText(10, 20, "Welcome to Space Invaders!");

    // Draw player spaceship
    painter.setBrush(Qt::green);
    painter.drawRect(player.getRect());
    painter.drawRect(player.getCannon());
    // Draw invaders, bullets, etc.
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed: " << event->key();
    if (event->key() == Qt::Key_Left)
        leftPressed = true;
    else if (event->key() == Qt::Key_Right)
        rightPressed = true;
    else if (event->key() == Qt::Key_Space)
        spacePressed = true;
    if (event->key() == Qt::Key_Escape) {
        emit goToMenu();
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Key released: " << event->key();
    if (event->key() == Qt::Key_Left)
        leftPressed = false;
    else if (event->key() == Qt::Key_Right)
        rightPressed = false;
    else if (event->key() == Qt::Key_Space)
        spacePressed = false;
    if (event->key() == Qt::Key_Escape) {
        emit goToMenu();
    }
}

void GameWindow::updateGame() {
    // Update player position based on key presses
    if (leftPressed)
        player.moveLeft();
    if (rightPressed)
        player.moveRight();

    // Update game state (invader movement, bullet movement, collision detection, etc.)

    // Update display
    update();
}

void GameWindow::start() {
    // Set initial player position
    player.setPos(200, 250);

    // Set initial bullet position (if necessary)
    bullet.setPos(0, 0);

    // Set initial invader position (if necessary)
    invader.setPos(0, 0);

    // Start the game timer
    if (!timer->isActive())
        timer->start(20); // Update game every 20 milliseconds

    // Reset key presses
    leftPressed = false;
    rightPressed = false;
    spacePressed = false;
}
