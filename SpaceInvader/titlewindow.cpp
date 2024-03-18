#include "titlewindow.h"

TitleWindow::TitleWindow(QWidget *parent)
    : QWidget(parent), gameWon(false)
{
    setStyleSheet("background-color: lightblue;");

    playButton = new QPushButton("Play", this);
    menuButton = new QPushButton("Menu", this);
    exitButton = new QPushButton("Exit", this);

    playButton->move(20, 20);
    menuButton->move(120, 20);
    exitButton->move(220, 20);

    connect(playButton, &QPushButton::clicked, this, &TitleWindow::handlePlayButtonClicked);
    connect(menuButton, &QPushButton::clicked, this, &TitleWindow::handleMenuButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &TitleWindow::handleExitButtonClicked);
}

void TitleWindow::setGameWon(bool won)
{
    gameWon = won;
    if (gameWon) {
        playButton->setText("Play again");
    }
    else {
        playButton->setText("Play");
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
