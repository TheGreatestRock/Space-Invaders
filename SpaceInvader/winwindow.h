// winwindow.h
#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class WinWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WinWindow(QWidget *parent = nullptr);

public slots:
    void setScore(int score);
    void setWin(bool win);
    void copyToClipboard();

private:
    QLabel *winLabel;
    QLabel *scoreLabel;
    QLabel *highScoreLabel;
    QPushButton *copyButton;
    void saveScore(int score);
    int getHighscore();
    void saveScoreToFile(int score);
};

#endif // WINWINDOW_H
