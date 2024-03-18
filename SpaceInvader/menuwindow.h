// menuwindow.h
#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QKeyEvent>

class MenuWindow : public QWidget {
    Q_OBJECT
public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void MainButtonClicked();

private slots:
    void handleColorBulletButtonClicked();
    void handleColorInvaderButtonClicked();
    void handleColorShipButtonClicked();
    void handleNbInvaderValueChanged(int value);
    void handleMusicUpload();
    void openColorPickerWindow(QPushButton *button);
    void returnToMain();
    void saveOptionsToFile();
    void loadOptionsFromFile();

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
    QLabel *nbInvaderLabel;
    QSpinBox *nbInvaderSpinBox;
    QPushButton *returnButton;
    QVector<QColor> colors;
    QHBoxLayout *musicLayout;
    QPushButton *uploadMusicButton;
    QLabel *musicPathLabel;
    QString musicFilePath;

};

#endif // MENUWINDOW_H
