// menuwindow.h
#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "colorpickerwindow.h"

class MenuWindow : public QWidget {
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

public slots:
    void handleColorBulletButtonClicked();
    void handleColorInvaderButtonClicked();
    void handleColorShipButtonClicked();
    void handleNbInvaderValueChanged(int value);
    void openColorPickerWindow();

signals:
    void goToMenu();

private:
    QPushButton *colorBulletButton;
    QPushButton *colorInvaderButton;
    QPushButton *colorShipButton;
    QSpinBox *nbInvaderSpinBox;
    QVBoxLayout *layout; // Declare layout here


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MENUWINDOW_H
