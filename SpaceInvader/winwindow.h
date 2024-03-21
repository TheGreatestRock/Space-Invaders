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
    void copyToClipboard();

private:
    QLabel *winLabel;
    QLabel *scoreLabel;
    QPushButton *copyButton;
};

#endif // WINWINDOW_H
