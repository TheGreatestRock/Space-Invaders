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
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include "colorpickerwindow.h"
#include "editorwindow.h"

class MenuWindow : public QWidget
{
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
    void handleShipEditorButtonClicked();
    void handleInvaderEditorButtonClicked();
    void handleBulletEditorButtonClicked();
    void handleBackgroundButtonClicked();
    void returnToMain();
    void handleNbInvaderValueChanged(int value);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void handleDrawingSaved(const QVector<QVector<bool>>& grid);

private:
    QVBoxLayout *layout;
    QHBoxLayout *bulletColorLayout;
    QLabel *bulletColorLabel;
    QPushButton *colorBulletButton;
    QPushButton *bulletEditorButton;
    QHBoxLayout *invaderColorLayout;
    QLabel *invaderColorLabel;
    QPushButton *colorInvaderButton;
    QPushButton *invaderEditorButton;
    QHBoxLayout *shipColorLayout;
    QLabel *shipColorLabel;
    QPushButton *colorShipButton;
    QPushButton *shipEditorButton;
    QHBoxLayout *nbInvaderLayout;
    QSpinBox *nbInvaderSpinBox;
    QPushButton *backgroundButton;
    QPushButton *returnButton;
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    QGraphicsPixmapItem *backgroundPixmapItem;

    QVector<QColor> colors;

    void openColorPickerWindow(QPushButton *button);
    void openEditorWindow(const QString& type);
    void saveOptionsToFile();
    void loadOptionsFromFile();
};

#endif // MENUWINDOW_H
