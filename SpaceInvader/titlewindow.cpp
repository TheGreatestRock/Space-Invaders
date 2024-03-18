#include "titlewindow.h"
#include "ui_titlewindow.h"

TitleWindow::TitleWindow(QWidget *parent)
    : QMainWindow(parent), gameWon(false)
{
    setStyleSheet("background-color: lightblue;");

    // Load the UI file
    ui.setupUi(this);

    // Connect button signals to slots
    connect(ui.playButton, &QPushButton::clicked, this, &TitleWindow::handlePlayButtonClicked);
    connect(ui.menuButton, &QPushButton::clicked, this, &TitleWindow::handleMenuButtonClicked);
    connect(ui.exitButton, &QPushButton::clicked, this, &TitleWindow::handleExitButtonClicked);
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
