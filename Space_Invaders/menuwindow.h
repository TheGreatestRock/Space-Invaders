// menuwindow.h
#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();
};

#endif // MENUWINDOW_H
