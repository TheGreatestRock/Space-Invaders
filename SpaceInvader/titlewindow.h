#ifndef TITLEWINDOW_H
#define TITLEWINDOW_H

#include <QWidget>
#include <QPushButton>

class TitleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWindow(QWidget *parent = nullptr);
    void setGameWon(bool won);

signals:
    void playButtonClicked();
    void menuButtonClicked();
    void exitButtonClicked();

private:
    QPushButton *playButton;
    QPushButton *menuButton;
    QPushButton *exitButton;
    bool gameWon;

private slots:
    void handlePlayButtonClicked();
    void handleMenuButtonClicked();
    void handleExitButtonClicked();
};

#endif // TITLEWINDOW_H
