#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    gameWon(false)
{
    ui->setupUi(this);
    setWindowTitle("Main Window");
    setStyleSheet("background-color: lightblue;");
    gameWindow = new GameWindow();
    menuWindow = new MenuWindow();
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::handlePlayButtonClicked);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWindow::handleOptionsButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::handleExitButtonClicked);
    connect(gameWindow, &GameWindow::goToMenu, this, &MainWindow::goToMenu);
    connect(gameWindow, &GameWindow::goToMenuWin, this, &MainWindow::goToMenuWin);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    if (gameWon) {
        QPainter painter(this);
        painter.setPen(QColor(255, 255, 255));
        painter.setFont(QFont("Arial", 30));
        painter.drawText(100, 100, "You Win!");
    }
}

void MainWindow::goToMenu()
{
    gameWon = false;
    menuWindow->setFocus();
    menuWindow->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(menuWindow);
}

void MainWindow::goToGame()
{
    gameWindow->setFocus();
    gameWindow->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(gameWindow);
}

void MainWindow::goToMenuWin()
{
    gameWon = true;
    menuWindow->setFocus();
    menuWindow->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(menuWindow);
    repaint();
}

void MainWindow::handlePlayButtonClicked()
{
    goToGame();
}

void MainWindow::handleOptionsButtonClicked()
{
    goToMenu();
}

void MainWindow::handleExitButtonClicked()
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete menuWindow;
    delete gameWindow;
}
