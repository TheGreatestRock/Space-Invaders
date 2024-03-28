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
#include <QCheckBox>
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
    void handleNbInvaderValueChanged(int value);
    void handleBackgroundButtonClicked();
    void handleDrawingSaved(const QVector<QVector<bool>>& grid);
    void openColorPickerWindow(QPushButton *button);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void saveOptionsToFile();
    void loadOptionsFromFile();
    void returnToMain();

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
    QLabel *nbInvaderLabel;
    QSpinBox *nbInvaderSpinBox;
    QVBoxLayout *bonusOptionsLayout;
    QLabel *bonusOptionsLabel;
    QHBoxLayout *bonusOptionsOptionsLayout;
    QPushButton *backgroundButton;
    QPushButton *returnButton;
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    QGraphicsPixmapItem *backgroundPixmapItem;
    QVector<QColor> colors;
    QSlider* invaderSpacingSlider;
    QSlider* bulletSpeedSlider;
    QSlider* fireRateSlider;
    QSlider* updateIntervalSlider;
    QCheckBox* useBonusOptionsCheckBox;
    QLabel *invaderSpacingLabel;
    QLabel *bulletSpeedLabel;
    QLabel *fireRateLabel;
    QLabel *updateIntervalLabel;
    QLabel *bonusOptionsToggleLabel;
    QTabWidget *tabWidget;
    QVBoxLayout *normalOptionsTabLayout;
    QVBoxLayout *bonusOptionsTabLayout;

    void toggleBonusOptionsVisibility();
    void openEditorWindow(const QString& type);
    void updateInvaderSpacing(int value);
    int invaderSpacing;
    void updateBulletSpeed(int value);
    int bulletSpeed;
    void updateFireRate(int value);
    int fireRate;
    void updateUpdateInterval(int value);
    int updateInterval;
    void updateUseBonusOptions(bool checked);
    bool useBonusOptions;
};

#endif // MENUWINDOW_H
