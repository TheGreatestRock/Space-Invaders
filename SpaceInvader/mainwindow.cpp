// mainwindow.cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameWindow = new GameWindow(this);
    setCentralWidget(gameWindow);

    menuWindow = new MenuWindow(this);

    connect(gameWindow, &GameWindow::goToMenu, this, &MainWindow::goToMenu);
}

MainWindow::~MainWindow()
{
    delete menuWindow;
}

void MainWindow::goToMenu()
{
    setCentralWidget(menuWindow);
}
