#include "titlewindow.h"
#include "ui_titlewindow.h"
#include <QFont>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>

TitleWindow::TitleWindow(QWidget *parent)
    : QMainWindow(parent), gameWon(false)
{
    setStyleSheet("background-color: lightblue;");

    // Load the UI file
    ui.setupUi(this);

    // Set font for the title label
    QFont titleLabelFont("Arial", 24, QFont::Bold);
    ui.titleLabel->setFont(titleLabelFont);

    // Set font for the high score label
    QFont highScoreLabelFont("Arial", 16);
    ui.highScoreLabel->setFont(highScoreLabelFont);

    QFont highScoreValueFont("Arial", 16);
    ui.highScoreValue->setFont(highScoreValueFont);

    QFont buttonFont("Arial", 14);
    ui.playButton->setFont(buttonFont);
    ui.menuButton->setFont(buttonFont);
    ui.exitButton->setFont(buttonFont);


    connect(ui.playButton, &QPushButton::clicked, this, &TitleWindow::handlePlayButtonClicked);
    connect(ui.menuButton, &QPushButton::clicked, this, &TitleWindow::handleMenuButtonClicked);
    connect(ui.exitButton, &QPushButton::clicked, this, &TitleWindow::handleExitButtonClicked);

    // Display high score
    int highscore = getHighscore();
    if (highscore == 0) {
        ui.highScoreValue->setText("No highscore yet");
    } else {
        ui.highScoreValue->setText(QString::number(highscore));
    }
}

void TitleWindow::setGameWon(bool won)
{
    gameWon = won;
    if (gameWon) {
        ui.playButton->setText("Play again");
    }
    else {
        ui.playButton->setText("Play");
    }
}

void TitleWindow::handlePlayButtonClicked()
{
    emit playButtonClicked();
}

void TitleWindow::handleMenuButtonClicked()
{
    emit menuButtonClicked();
}

void TitleWindow::handleExitButtonClicked()
{
    emit exitButtonClicked();
}

int TitleWindow::getHighscore(){
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
    return highscore;
}
