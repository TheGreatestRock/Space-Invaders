#ifndef TITLEWINDOW_H
#define TITLEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "ui_titlewindow.h" // Include the generated UI header

class TitleWindow : public QMainWindow // Change QWidget to QMainWindow
{
    Q_OBJECT

public:
    explicit TitleWindow(QWidget *parent = nullptr);

    // Function to set game status
    void setGameWon(bool won);

signals:
    // Signals for button clicks
    void playButtonClicked();
    void menuButtonClicked();
    void exitButtonClicked();

private slots:
    // Slots for handling button clicks
    void handlePlayButtonClicked();
    void handleMenuButtonClicked();
    void handleExitButtonClicked();

private:
    Ui::MainWindow ui; // UI object
    bool gameWon;      // Game status
    int getHighscore();
};

#endif // TITLEWINDOW_H
