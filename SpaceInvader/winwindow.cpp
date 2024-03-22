// winwindow.cpp
#include "winwindow.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>


WinWindow::WinWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    winLabel = new QLabel("You win", this);
    highScoreLabel = new QLabel("Highscore: ", this);
    scoreLabel = new QLabel("Score: ", this);
    copyButton = new QPushButton("Copy to Clipboard", this);

    QFont labelFont("Papyrus", 16);
    winLabel->setFont(labelFont);
    scoreLabel->setFont(labelFont);
    highScoreLabel->setFont(labelFont);

    winLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setAlignment(Qt::AlignCenter);
    highScoreLabel->setAlignment(Qt::AlignCenter);

    winLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    scoreLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    highScoreLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    layout->addWidget(winLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(highScoreLabel);
    layout->addWidget(copyButton);

    // Center the window on the screen
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(400, 300), // Set window size to 400x300
            qApp->primaryScreen()->availableGeometry()
            )
        );

    setLayout(layout);

    connect(copyButton, &QPushButton::clicked, this, &WinWindow::copyToClipboard);
}

void WinWindow::saveScore(int score) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(path);
    }
    QFile file(path + "/highscore");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }
    QTextStream in(&file);
    QString highscore;
    int currentHighscore = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("highscore:")) {
            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                currentHighscore = parts[1].toInt();
            }
        }
    }
    if (score > currentHighscore) {
        file.resize(0);
        in << "highscore: " << score << "\n";
    }
    file.close();
    saveScoreToFile(score);
}

void WinWindow::saveScoreToFile(int score) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile file(path + "/highscore");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }
    QTextStream out(&file);
    out << "score: " << score << " " << QDateTime::currentDateTime().toString("ddd MMM d hh:mm:ss yyyy") << "\n";
    file.close();
}

int WinWindow::getHighscore(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile file(path + "/highscore");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file";
    }
    QTextStream in(&file);
    int highscore = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("highscore:")) {
            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                highscore = parts[1].toInt();
                break;
            }
        }
    }
    file.close();
    if (highscore == 0) {
        highScoreLabel->setText("No highscore yet");
    } else {
        highScoreLabel->setText("Highscore: " + QString::number(highscore));
    }
    return highscore;
}

void WinWindow::setScore(int score)
{
    saveScore(score);
    getHighscore();
    scoreLabel->setText("Score: " + QString::number(score));
    show();
}

void WinWindow::copyToClipboard()
{
    QString textToCopy = scoreLabel->text() + "\n" + highScoreLabel->text();
    QApplication::clipboard()->setText(textToCopy);
}
