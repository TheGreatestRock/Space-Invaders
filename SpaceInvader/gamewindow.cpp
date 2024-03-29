#include "gamewindow.h"
#include "qrandom.h"
#include <QPainter>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QSoundEffect>
#include <QKeyEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), score(0)
{
    qDebug() << "GameWindow constructor";
    checkSaveFiles();
    player = new Player(width()/2, (9*height())/10, PLAYER_SIZE, Qt::white);
    timer = new QTimer(this);
    winWindow =  new WinWindow();
    winWindow->hide();
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    connect(this, &GameWindow::WinEvent, winWindow, &WinWindow::setScore);
    connect(this, &GameWindow::LoseEvent, winWindow, &WinWindow::setScore);
    connect(invaderShootTimer, &QTimer::timeout, this, &GameWindow::handleInvaderShoot);
    timer->start(UPDATE_INTERVAL);
    invaderShootTimer->start(INVADER_SHOOT_INTERVAL);
    qDebug() << timer->isActive();
    leftPressed = false;
    rightPressed = false;
    resetGame();
    timer->stop();
    invaderShootTimer->stop();
}


//this function basically checks if there are local save files, if not it creates them
void GameWindow::checkSaveFiles() {
    //for the option file 
    qDebug() << "Checking save files";
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "Creating save files";
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << "ListOfColors:#ffffff\n";
            out << "ShipColor:#ffffff\n";
            out << "BulletColor:#ffffff\n";
            out << "InvaderColor:#ffffff\n";
            out << "PowerupColor:#ffffff\n";
            out << "NumberOfInvaders: 50\n";
            file.close();
        }
        else {
            qDebug() << "Could not open file";
        }
    }
    
    //create the file for the score
    qDebug() << "Checking score files";
    QString filePathScore = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/score";
    QDir().mkpath(QFileInfo(filePathScore).absoluteDir().path());
    QFile fileScore(filePathScore);
    if (!fileScore.exists()) {
        qDebug() << "Creating score files";
        if (fileScore.open(QIODevice::WriteOnly)) {
            QTextStream out(&fileScore);
            out << "\n";
            fileScore.close();
        }
        else {
            qDebug() << "Could not open file";
        }
    }

    //create the basic files for the bullets, invaders and player looks
    qDebug() << "Checking save files";
    QString filePathBullets = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Bullet";
    QDir().mkpath(QFileInfo(filePathBullets).absoluteDir().path());
    QFile fileBullets(filePathBullets);
    if (!fileBullets.exists()) {
        qDebug() << "Creating bulelt look";
        if (fileBullets.open(QIODevice::WriteOnly)) {
            QTextStream out(&fileBullets);
            out << "0 0 0 0 1 0 0 0 0 0 \n";
            out << "0 0 0 1 1 1 0 0 0 0 \n";
            out << "0 0 0 1 1 1 0 0 0 0 \n";
            out << "0 0 0 1 1 1 0 0 0 0 \n";
            out << "0 0 1 1 1 1 1 0 0 0 \n";
            out << "0 0 0 0 1 0 0 0 0 0 \n";
            out << "0 0 0 0 1 0 0 0 0 0 \n";
            out << "0 0 0 0 0 0 0 0 0 0 \n";
            out << "0 0 0 0 0 0 0 0 0 0 \n";
            out << "0 0 0 0 0 0 0 0 0 0 \n";
            fileBullets.close();
        }
        else {
            qDebug() << "Could not open file";
        }
    }

    qDebug() << "Checking invader look";
    QString filePathInvaders = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Invader";
    QDir().mkpath(QFileInfo(filePathInvaders).absoluteDir().path());
    QFile fileInvaders(filePathInvaders);
    if (!fileInvaders.exists()) {
        qDebug() << "Creating invader look";
        if (fileInvaders.open(QIODevice::WriteOnly)) {
            QTextStream out(&fileInvaders);
            out << "0 0 1 0 0 0 0 1 0 0 \n";
            out << "0 0 0 1 0 0 1 0 0 0 \n";
            out << "0 0 0 1 1 1 1 0 0 0 \n";
            out << "0 1 1 0 1 1 0 1 1 0 \n";
            out << "1 1 1 1 1 1 1 1 1 1 \n";
            out << "1 0 1 1 1 1 1 1 0 1 \n";
            out << "1 0 1 0 0 0 0 1 0 1 \n";
            out << "0 0 0 1 0 0 1 0 0 0 \n";
            out << "0 0 0 0 0 0 0 0 0 0 \n";
            out << "0 0 0 0 0 0 0 0 0 0 \n";
            fileInvaders.close();
        }
        else {
            qDebug() << "Could not open file";
        }
    }

    qDebug() << "Checking player look";
    QString filePathPlayer = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Ship";
    QDir().mkpath(QFileInfo(filePathPlayer).absoluteDir().path());
    QFile filePlayer(filePathPlayer);
    if (!filePlayer.exists()) {
        qDebug() << "Creating player look";
        if (filePlayer.open(QIODevice::WriteOnly)) {
            QTextStream out(&filePlayer);
            out << "0 0 0 0 0 0 0 0 0 0 \n"; 
            out << "0 0 0 0 1 1 0 0 0 0 \n"; 
            out << "0 0 0 0 1 1 0 0 0 0 \n"; 
            out << "0 1 1 0 1 1 0 1 1 0 \n"; 
            out << "1 0 1 1 0 0 1 1 0 1 \n"; 
            out << "1 0 1 1 0 0 1 1 0 1 \n"; 
            out << "1 0 1 1 1 1 1 1 0 1 \n"; 
            out << "0 1 1 1 1 1 1 1 1 0 \n"; 
            out << "0 0 1 1 0 0 1 1 0 0 \n"; 
            out << "0 0 0 0 0 0 0 0 0 0 \n"; 
            filePlayer.close();
        }
        else {
            qDebug() << "Could not open file";
        }
    }



    QString resourcePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(resourcePath + "/sfx"); // Create the 'sfx' directory if it doesn't exist

    // Set up the network access manager
    qDebug() << "Downloading sound files";
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &GameWindow::handleDownloadFinished);

    // Download sound files from GitHub repository
    qDebug() << "Downloading sound files";
    QStringList soundFiles = {"/Laser_Shoot.wav", "/Explosion.wav", "/Explosion2.wav"};
    QString githubRepoUrl = "https://raw.githubusercontent.com/TheGreatestRock/Space-Invaders/main/sfx";
    for (const QString& soundFile : soundFiles) {
        QString fileUrl = githubRepoUrl + soundFile;
        QUrl url(fileUrl);
        QNetworkRequest request(url);
        networkAccessManager->get(request);
    }

}

void GameWindow::handleDownloadFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString soundFile = reply->url().toString().remove(0, reply->url().toString().lastIndexOf('/') + 1);
        QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/sfx/" + soundFile;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        } else {
            qDebug() << "Could not open file: " << filePath;
        }
    } else {
        qDebug() << "Download error: " << reply->errorString();
    }

    reply->deleteLater();
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
                    if (value != "")
                        playerColor = QColor(value);
                    else
                        playerColor = Qt::white;
                    qDebug() << "ShipColor: " << value << " converted to: " << playerColor;
                }
                else if (key == "BulletColor") {
                    if (value != "")
                        bulletColor = QColor(value);
                    else
                        bulletColor = Qt::white;
                    qDebug() << "BulletColor: " << value << " converted to: " << bulletColor;
                }
                else if (key == "InvaderColor") {
                    if (value != "")
                        invaderColor = QColor(value);
                    else
                        invaderColor = Qt::white;
                    qDebug() << "InvaderColor: " << value << " converted to: " << invaderColor;
                }
                else if (key == "PowerupColor") {
                    if (value != "")
                        powerupColor = QColor(value);
                    else
                        powerupColor = Qt::white;
                    qDebug() << "PowerupColor: " << value << " converted to: " << invaderColor;
                }
                else if (key == "NumberOfInvaders") {
                    numberOfInvaders = value.toInt();
                    qDebug() << "NumberOfInvaders: " << value << " converted to: " << numberOfInvaders;
                }
                else if (key == "UseBonusOptions") {
                    if (value == "true") {
                        line = in.readLine();
                        if (line.startsWith("InvaderSpacing:")) {
                            INVADER_SPACING = line.split(":").last().toInt();
                        }
                        line = in.readLine();
                        if (line.startsWith("BulletSpeed:")) {
                            BULLET_SPEED = line.split(":").last().toInt();
                        }
                        line = in.readLine();
                        if (line.startsWith("FireRate:")) {
                            FIRE_RATE = line.split(":").last().toInt();
                        }
                        line = in.readLine();
                        if (line.startsWith("UpdateInterval:")) {
                            UPDATE_INTERVAL = line.split(":").last().toInt();
                        }
                    }
                }
            }
        }
        file.close();
    }
    else {
        qDebug() << "Could not open file";
    }
}

void GameWindow::handleInvaderShoot() {
    if (!invader.isEmpty() && timer->isActive()) {
        // Select a random invader
        int index = (new QRandomGenerator(QDateTime::currentMSecsSinceEpoch()))->bounded(invader.size());
        Invader* invad = invader.at(index);

        // Create a new bullet at the invader's position
        Bullet* newBullet = new Bullet(invad->getRect().left() + invad->getRect().width()/2, invad->getRect().bottom(), BULLET_SPEED, bulletColor, false, false);
        bullets.append(newBullet);
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
    player = new Player(width()/2, (9*height())/10, PLAYER_SIZE, playerColor);
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
    if (!invaderShootTimer->isActive())
        invaderShootTimer->start(INVADER_SHOOT_INTERVAL);
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
    QString resourcePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    laserShootSound = new QSoundEffect(this);
    laserShootSound->setSource(QUrl::fromLocalFile(resourcePath + "/sfx/Laser_Shoot.wav"));

    explosionInvaderSound = new QSoundEffect(this);
    explosionInvaderSound->setSource(QUrl::fromLocalFile(resourcePath + "/sfx/Explosion.wav"));

    explosionPlayerSound = new QSoundEffect(this);
    explosionPlayerSound->setSource(QUrl::fromLocalFile(resourcePath + "/sfx/Explosion2.wav"));
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
    painter.setBrush(player->getColor());
    QVector<QVector<int>> playerPattern = player->getPattern();
    for (int i = 0; i < playerPattern.size(); ++i) {
        for (int j = 0; j < playerPattern.at(i).size(); ++j) {
            if (playerPattern.at(i).at(j) == 1) {
                painter.drawRect(player->getRect().left() + j, player->getRect().top() + i * 2, 2, 2);
            }
        }
    }

    // Draw bullets
    for (Bullet* bullet : qAsConst(bullets)) {
        painter.setBrush(bullet->getColor());
        QVector<QVector<int>> bulletPattern = bullet->getPattern();
        for (int i = 0; i < bulletPattern.size(); ++i) {
            for (int j = 0; j < bulletPattern.at(i).size(); ++j) {
                if (bulletPattern.at(i).at(j) == 1) {
                    int yPosition = bullet->getRect().top() + (!bullet->getIsShipBullet() ? bulletPattern.size() - 1 - i : i) * 2;
                    painter.drawRect(bullet->getRect().left() + j, yPosition, 2, 2);
                }
            }
        }
    }

    // Draw invaders
    for (Invader* invad : qAsConst(invader)) {
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
            Bullet* newBullet = new Bullet(player->getCannon().left() + player->getCannon().width()/2, player->getCannon().top(), BULLET_SPEED, bulletColor, true, false);
            bullets.append(newBullet);
            firerate = FIRE_RATE;
            laserShootSound->play();
        } else {
            qDebug() << "cannot shoot " << firerate;
        }
    }
    if (event->key() == Qt::Key_Escape) {
        timer->stop();
        invaderShootTimer->stop();
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
    if (invaderMoveTimer == 0 && timer->isActive()) {
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
            if (invad->getRect().bottom() > player->getRect().top()) {
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
            if (!bullets.at(i)->getIsShipBullet()) {
                continue;
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

    // Check bullet/player(ship) collision
    for (int i = 0; i < bullets.size(); ++i) {
        if (bullets.at(i)->getRect().intersects(player->getRect()) && !bullets.at(i)->getIsShipBullet()) {
            winWindow->setWin(false);
            emit LoseEvent(score);
            timer->stop();
            winWindow->show();
            explosionPlayerSound->play();
        }
    }

    // Update player position based on key presses
    if (leftPressed && player->getRect().left() > 0){
        player->moveLeft();
        qDebug() << "Player moved left";
    }
    if (rightPressed && player->getRect().right() < width() - player->getRect().width()/2){
        player->moveRight();
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
    for (Bullet* bullet : qAsConst(bullets)) {
        delete bullet;
    }
    for (Invader* inv : qAsConst(invader)) {
        delete inv;
    }
    delete laserShootSound;
    delete explosionInvaderSound;
    delete explosionPlayerSound;
}
