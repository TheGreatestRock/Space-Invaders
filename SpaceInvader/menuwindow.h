#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QKeyEvent>
#include <QDebug>
#include "colorpickerwindow.h"

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void goToMenu();

private slots:
    void handleColorBulletButtonClicked();
    void handleColorInvaderButtonClicked();
    void handleColorShipButtonClicked();
    void handleNbInvaderValueChanged(int value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QVBoxLayout *layout;
    QPushButton *colorBulletButton;
    QPushButton *colorInvaderButton;
    QPushButton *colorShipButton;
    QSpinBox *nbInvaderSpinBox;

    void openColorPickerWindow();
};

#endif // MENUWINDOW_H
