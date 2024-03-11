// menuwindow.h
#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QDebug>

class MenuWindow : public QWidget
{
    Q_OBJECT

signals:
    void goToGame();
    
public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();
    void start();
};

#endif // MENUWINDOW_H
