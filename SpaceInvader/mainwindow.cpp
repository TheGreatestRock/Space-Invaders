#include "mainwindow.h"
#include "gamewindow.h"
#include "menuwindow.h"
#include "titlewindow.h"
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    titleWindow(new TitleWindow()),
    gameWindow(new GameWindow()),
    menuWindow(new MenuWindow()),
    gameWon(false)
{
    createSaveFile();
    setWindowTitle("Main Window");
    setStyleSheet("background-color: lightblue;");

    setMinimumSize(800, 600);

    connect(titleWindow, &TitleWindow::playButtonClicked, this, &MainWindow::handlePlayButtonClicked);
    connect(titleWindow, &TitleWindow::menuButtonClicked, this, &MainWindow::handleOptionsButtonClicked);
    connect(titleWindow, &TitleWindow::exitButtonClicked, this, &MainWindow::handleExitButtonClicked);
    connect(gameWindow, &GameWindow::MainButtonClicked, this, &MainWindow::handleMainButtonClicked);
    connect(gameWindow, &GameWindow::WinEvent, this, &MainWindow::handleWin);
    connect(menuWindow, &MenuWindow::MainButtonClicked, this, &MainWindow::handleMainButtonClicked);

    // Initially, only the title window should be shown
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titleWindow);
    layout->addWidget(gameWindow);
    layout->addWidget(menuWindow);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    gameWindow->hide();
    menuWindow->hide();
}

void MainWindow::goToMenu()
{
    gameWindow->hide();
    titleWindow->hide();
    menuWindow->show();
    menuWindow->setFocus();
}

void MainWindow::goToGame()
{
    gameWindow->resetGame();
    titleWindow->hide();
    menuWindow->hide();
    gameWindow->show();
    gameWindow->setFocus();
}

void MainWindow::goToMain()
{
    gameWindow->hide();
    menuWindow->hide();
    titleWindow->show();
    titleWindow->setFocus();
}

void MainWindow::goToMainWin()
{
    gameWon = true;
    titleWindow->setGameWon(true);
    goToMain();
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

void MainWindow::handleMainButtonClicked()
{
    goToMain();
}

void MainWindow::handleWin()
{
    goToMainWin();
}

MainWindow::~MainWindow()
{
    delete titleWindow;
    delete gameWindow;
    delete menuWindow;
}

void MainWindow::createSaveFile(){
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
    QFile file(filePath);
    if (file.size() == 0) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "ListOfColors:" << Qt::endl;
            out << "BulletColor:#FFFFFF"  << Qt::endl;
            out << "InvaderColor:#00FF00" << Qt::endl;
            out << "ShipColor:#FFFFFF" << Qt::endl;
            out << "NumberOfInvaders:10" << Qt::endl;
            file.close();
            qDebug() << "Base save file created.";
        } else {
            qDebug() << "Failed to create base save file.";
        }
    } else {
        qDebug() << "Save file already exists.";
    }
}
