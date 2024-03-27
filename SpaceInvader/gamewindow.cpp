#include "gamewindow.h"
#include <QPainter>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QSoundEffect>
#include <QKeyEvent>

const int PLAYER_SIZE = 5;
const int INVADER_SIZE = 5;
const int INVADER_SPACING = 30;
const int BULLET_SPEED = 12;
const int FIRE_RATE = 5;
const int SCORE_PER_INVADER = 10;
const int UPDATE_INTERVAL = 20;

GameWindow::GameWindow(QWidget *parent) : QWidget(parent),
    player(width()/2, (9*height())/10, PLAYER_SIZE, Qt::white), score(0)
{
    qDebug() << "GameWindow constructor";
    timer = new QTimer(this);
    winWindow =  new WinWindow();
    winWindow->hide();
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    connect(this, &GameWindow::WinEvent, winWindow, &WinWindow::setScore);
    connect(this, &GameWindow::LoseEvent, winWindow, &WinWindow::setScore);
    timer->start(UPDATE_INTERVAL); // Update game every 20 milliseconds
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
    clearBulletsAndInvaders();
    initializePlayerAndInvaders();
    restartTimerIfNotActive();
    resetKeyPresses();
    resetGameParameters();
    initializeSounds();
    update();
}

void GameWindow::clearBulletsAndInvaders() {
    qDeleteAll(bullets);
    bullets.clear();
    qDeleteAll(invader);
    invader.clear();
}

void GameWindow::initializePlayerAndInvaders() {
    player = Player(width()/2, (9*height())/10, PLAYER_SIZE, playerColor);
    for (int i = 0; i < numberOfInvaders; ++i) {
        int row = i / 10;
        int col = i % 10;
        int x = INVADER_SPACING + col * (INVADER_SIZE + INVADER_SPACING);
        int y = 50 + row * 20;
        invader.append(new Invader(x, y, INVADER_SIZE, invaderColor));
    }
}

void GameWindow::restartTimerIfNotActive() {
    if (!timer->isActive())
        timer->start(UPDATE_INTERVAL);
}

void GameWindow::resetKeyPresses() {
    leftPressed = false;
    rightPressed = false;
}

void GameWindow::resetGameParameters() {
    score = 0;
    firerate = 0;
    invaderMoveTimer = 0;
}

void GameWindow::initializeSounds() {
    laserShootSound = new QSoundEffect(this);
    laserShootSound->setSource(QUrl::fromLocalFile("C:/Users/thegr/Documents/Cours_IUT_2023_2024/S4/C++/Space Invader/SpaceInvader/sfx/Laser_Shoot.wav"));

    explosionInvaderSound = new QSoundEffect(this);
    explosionInvaderSound->setSource(QUrl::fromLocalFile("C:/Users/thegr/Documents/Cours_IUT_2023_2024/S4/C++/Space Invader/SpaceInvader/sfx/Explosion.wav"));

    explosionPlayerSound = new QSoundEffect(this);
    explosionPlayerSound->setSource(QUrl::fromLocalFile("C:/Users/thegr/Documents/Cours_IUT_2023_2024/S4/C++/Space Invader/SpaceInvader/sfx/Explosion2.wav"));
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
        painter.setBrush(bullet->getColor());
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
            Bullet* newBullet = new Bullet(player.getCannon().left() + player.getCannon().width()/2, player.getCannon().top(), BULLET_SPEED, bulletColor);
            bullets.append(newBullet);
            firerate = FIRE_RATE;
            laserShootSound->play();
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
    if (invaderMoveTimer == 0) {
        // Update invaders position
        for (int i = 0; i < invader.size(); ++i) {
            Invader* invad = invader.at(i);
            invad->move();
            // Check if invader is out of bounds, change direction if so
            if (invad->getRect().right() > width() || invad->getRect().left() < 0) {
                for (int j = 0; j < invader.size(); ++j) {
                    invader[j]->hitWall();
                }
                break;
            }
            // Check if invader is at the same level as the player then emit LoseEvent
            if (invad->getRect().bottom() > player.getRect().top()) {
                winWindow->setWin(false);
                emit LoseEvent(score);
                timer->stop();
                winWindow->show();
                explosionPlayerSound->play();
            }
        }
        //decrease the time when there are less invaders
        invaderMoveTimer = invader.size() / 10;
    } else {
        invaderMoveTimer--;
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
                    invader[k]->setSpeed(invader[k]->getSpeed() * 1.01);
                    qDebug() << "Speed : " << invader[k]->getSpeed();
                }
                score += SCORE_PER_INVADER;
                explosionInvaderSound->play();
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
    delete laserShootSound;
    delete explosionInvaderSound;
    delete explosionPlayerSound;
}
