// menuwindow.h
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
#include <QColorDialog>
#include <QVector>
#include <QStandardPaths>
#include <QDir>
#include "colorpickerwindow.h"
#include "editorwindow.h"

class MenuWindow : public QWidget {
    Q_OBJECT
public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void MainButtonClicked();

private slots:
    void handleColorBulletButtonClicked();
    void handleColorInvaderButtonClicked();
    void handleColorShipButtonClicked();
    void handleNbInvaderValueChanged(int value);
    void returnToMain();

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
    QPushButton *returnButton;
    QVector<QColor> colors;
    QPushButton *shipEditorButton;
    QPushButton *invaderEditorButton;
    QPushButton *bulletEditorButton;
    void openColorPickerWindow(QPushButton *button);
    void saveOptionsToFile();
    void loadOptionsFromFile();
};

#endif // MENUWINDOW_H
