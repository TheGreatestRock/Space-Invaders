#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QDebug>
#include <QKeyEvent>
#include "colorpickerwindow.h"

class MenuWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void goToMain();

private slots:
    void handleColorBulletButtonClicked();
    void handleColorInvaderButtonClicked();
    void handleColorShipButtonClicked();
    void handleNbInvaderValueChanged(int value);
    void returnToMain(); // Declaration of the new slot

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QVBoxLayout *layout;
    QHBoxLayout *bulletColorLayout;
    QLabel *bulletColorLabel;
    QPushButton *colorBulletButton;
    QHBoxLayout *invaderColorLayout;
    QLabel *invaderColorLabel;
    QPushButton *colorInvaderButton;
    QHBoxLayout *shipColorLayout;
    QLabel *shipColorLabel;
    QPushButton *colorShipButton;
    QHBoxLayout *nbInvaderLayout;
    QSpinBox *nbInvaderSpinBox;
    QVector<QColor> colors;
    QPushButton *returnButton; // Declaration of the return button

    void openColorPickerWindow(QPushButton *button = nullptr);
};

#endif // MENUWINDOW_H
