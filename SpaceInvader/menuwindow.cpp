#include "menuwindow.h"
#include <QGraphicsItem>
#include "colorpickerwindow.h"
#include "editorwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

#include "menuwindow.h"
#include <QGraphicsItem>
#include "colorpickerwindow.h"
#include "editorwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

MenuWindow::MenuWindow(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    tabWidget = new QTabWidget(this);

    QWidget *normalOptionsTab = new QWidget(this);
    QWidget *bonusOptionsTab = new QWidget(this);

    normalOptionsTabLayout = new QVBoxLayout(normalOptionsTab);
    bonusOptionsTabLayout = new QVBoxLayout(bonusOptionsTab);

    normalOptionsTab->setLayout(normalOptionsTabLayout);
    bonusOptionsTab->setLayout(bonusOptionsTabLayout);

    tabWidget->addTab(normalOptionsTab, "Normal Options");
    tabWidget->addTab(bonusOptionsTab, "Bonus Options (WIP)");

    bulletColorLayout = new QHBoxLayout();
    bulletColorLabel = new QLabel("Bullet Color:", this);
    colorBulletButton = new QPushButton("Change color", this);
    bulletEditorButton = new QPushButton("Bullet Editor", this);
    bulletColorLayout->addWidget(bulletColorLabel);
    bulletColorLayout->addWidget(colorBulletButton);
    bulletColorLayout->addWidget(bulletEditorButton);

    powerupColorLayout = new QHBoxLayout();
    powerupColorLabel = new QLabel("Powerup Color:", this);
    colorPowerupButton = new QPushButton("Change color", this);
    powerupEditorButton = new QPushButton("Powerup Editor", this);
    powerupColorLayout->addWidget(powerupColorLabel);
    powerupColorLayout->addWidget(colorPowerupButton);
    powerupColorLayout->addWidget(powerupEditorButton);

    invaderColorLayout = new QHBoxLayout();
    invaderColorLabel = new QLabel("Invader Color:", this);
    colorInvaderButton = new QPushButton("Change color", this);
    invaderEditorButton = new QPushButton("Invader Editor", this);
    invaderColorLayout->addWidget(invaderColorLabel);
    invaderColorLayout->addWidget(colorInvaderButton);
    invaderColorLayout->addWidget(invaderEditorButton);

    shipColorLayout = new QHBoxLayout();
    shipColorLabel = new QLabel("Ship Color:", this);
    colorShipButton = new QPushButton("Change color", this);
    shipEditorButton = new QPushButton("Ship Editor", this);
    shipColorLayout->addWidget(shipColorLabel);
    shipColorLayout->addWidget(colorShipButton);
    shipColorLayout->addWidget(shipEditorButton);

    nbInvaderLayout = new QHBoxLayout();
    nbInvaderLabel = new QLabel("Number of Invader:", this);
    nbInvaderSpinBox = new QSpinBox(this);
    nbInvaderSpinBox->setRange(1, 100);
    nbInvaderSpinBox->setValue(5);
    nbInvaderLayout->addWidget(nbInvaderLabel);
    nbInvaderLayout->addWidget(nbInvaderSpinBox);

    invaderSpacingSlider = new QSlider(Qt::Horizontal, this);
    invaderSpacingSlider->setRange(10, 100);
    invaderSpacingSlider->setValue(invaderSpacing);
    invaderSpacingLabel = new QLabel("Invader Spacing:", this);
    connect(invaderSpacingSlider, &QSlider::valueChanged, this, &MenuWindow::updateInvaderSpacing);

    bulletSpeedSlider = new QSlider(Qt::Horizontal, this);
    bulletSpeedSlider->setRange(1, 50);
    bulletSpeedSlider->setValue(bulletSpeed);
    bulletSpeedLabel = new QLabel("Bullet Speed:", this);
    connect(bulletSpeedSlider, &QSlider::valueChanged, this, &MenuWindow::updateBulletSpeed);

    fireRateSlider = new QSlider(Qt::Horizontal, this);
    fireRateSlider->setRange(1, 20);
    fireRateSlider->setValue(fireRate);
    fireRateLabel = new QLabel("Fire Rate:", this);
    connect(fireRateSlider, &QSlider::valueChanged, this, &MenuWindow::updateFireRate);

    updateIntervalSlider = new QSlider(Qt::Horizontal, this);
    updateIntervalSlider->setRange(1, 100);
    updateIntervalSlider->setValue(updateInterval);
    updateIntervalLabel = new QLabel("Update Interval:", this);
    connect(updateIntervalSlider, &QSlider::valueChanged, this, &MenuWindow::updateUpdateInterval);

    // Resize the sliders
    invaderSpacingSlider->setMinimumHeight(20);
    invaderSpacingSlider->setMaximumHeight(20);
    bulletSpeedSlider->setMinimumHeight(20);
    bulletSpeedSlider->setMaximumHeight(20);
    fireRateSlider->setMinimumHeight(20);
    fireRateSlider->setMaximumHeight(20);
    updateIntervalSlider->setMinimumHeight(20);
    updateIntervalSlider->setMaximumHeight(20);

    // Add widgets to the normal options tab layout
    normalOptionsTabLayout->addLayout(bulletColorLayout);
    normalOptionsTabLayout->addLayout(powerupColorLayout);
    normalOptionsTabLayout->addLayout(invaderColorLayout);
    normalOptionsTabLayout->addLayout(shipColorLayout);
    normalOptionsTabLayout->addLayout(nbInvaderLayout);

    // Add widgets to the bonus options tab layout
    bonusOptionsLayout = new QVBoxLayout();
    useBonusOptionsCheckBox = new QCheckBox("Use Bonus Options", this);
    useBonusOptionsCheckBox->setChecked(useBonusOptions);
    connect(useBonusOptionsCheckBox, &QCheckBox::clicked, this, &MenuWindow::updateUseBonusOptions);
    bonusOptionsLayout->addWidget(useBonusOptionsCheckBox);
    bonusOptionsTabLayout->addLayout(bonusOptionsLayout);
    bonusOptionsTabLayout->addWidget(invaderSpacingLabel);
    bonusOptionsTabLayout->addWidget(invaderSpacingSlider);
    bonusOptionsTabLayout->addWidget(bulletSpeedLabel);
    bonusOptionsTabLayout->addWidget(bulletSpeedSlider);
    bonusOptionsTabLayout->addWidget(fireRateLabel);
    bonusOptionsTabLayout->addWidget(fireRateSlider);
    bonusOptionsTabLayout->addWidget(updateIntervalLabel);
    bonusOptionsTabLayout->addWidget(updateIntervalSlider);

    backgroundButton = new QPushButton("Background (WIP)", this);
    returnButton = new QPushButton("Return to Main", this);

    connect(colorBulletButton, &QPushButton::clicked, this, &MenuWindow::handleColorBulletButtonClicked);
    connect(colorInvaderButton, &QPushButton::clicked, this, &MenuWindow::handleColorInvaderButtonClicked);
    connect(colorPowerupButton, &QPushButton::clicked, this, &MenuWindow::handleColorPowerupButtonClicked);
    connect(colorShipButton, &QPushButton::clicked, this, &MenuWindow::handleColorShipButtonClicked);
    connect(nbInvaderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuWindow::handleNbInvaderValueChanged);
    connect(returnButton, &QPushButton::clicked, this, &MenuWindow::returnToMain);
    connect(backgroundButton, &QPushButton::clicked, this, &MenuWindow::handleBackgroundButtonClicked);
    connect(shipEditorButton, &QPushButton::clicked, this, &MenuWindow::handleShipEditorButtonClicked);
    connect(powerupEditorButton, &QPushButton::clicked, this, &MenuWindow::handlePowerUpEditorButtonClicked);
    connect(invaderEditorButton, &QPushButton::clicked, this, &MenuWindow::handleInvaderEditorButtonClicked);
    connect(bulletEditorButton, &QPushButton::clicked, this, &MenuWindow::handleBulletEditorButtonClicked);

    layout->addWidget(tabWidget);
    layout->addWidget(backgroundButton);
    layout->addWidget(returnButton);
    setLayout(layout);

    loadOptionsFromFile();

    graphicsScene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(graphicsScene);
    backgroundPixmapItem = nullptr;
}

void MenuWindow::toggleBonusOptionsVisibility() {

}

void MenuWindow::handleColorBulletButtonClicked() {
    openColorPickerWindow(colorBulletButton);
}

void MenuWindow::handleColorInvaderButtonClicked() {
    openColorPickerWindow(colorInvaderButton);
}

void MenuWindow::handleColorShipButtonClicked() {
    openColorPickerWindow(colorShipButton);
}

void MenuWindow::handleColorPowerupButtonClicked() {
    openColorPickerWindow(colorPowerupButton);
}

void MenuWindow::handleShipEditorButtonClicked() {
    openEditorWindow("Ship");
}

void MenuWindow::handleInvaderEditorButtonClicked() {
    openEditorWindow("Invader");
}

void MenuWindow::handleBulletEditorButtonClicked() {
    openEditorWindow("Bullet");
}

void MenuWindow::handlePowerUpEditorButtonClicked(){
    openEditorWindow("Powerup");
}

void MenuWindow::handleDrawingSaved(const QVector<QVector<bool>>& grid)
{
    qDebug() << "Drawing saved";
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j]) {
                QGraphicsRectItem *rect = graphicsScene->addRect(j * 10, i * 10, 10, 10, QPen(Qt::black), QBrush(Qt::black));
            }
        }
    }
}


void MenuWindow::updateInvaderSpacing(int value) {
    invaderSpacing = value;
    invaderSpacingLabel->setText("Invader Spacing: " + QString::number(value));
    saveOptionsToFile();
}

void MenuWindow::updateBulletSpeed(int value) {
    bulletSpeed = value;
    bulletSpeedLabel->setText("Bullet Speed: " + QString::number(value));
    saveOptionsToFile();
}

void MenuWindow::updateFireRate(int value) {
    fireRate = value;
    fireRateLabel->setText("Fire Rate: " + QString::number(value));
    saveOptionsToFile();
}

void MenuWindow::updateUpdateInterval(int value) {
    updateInterval = value;
    updateIntervalLabel->setText("Update Interval: " + QString::number(value));
    saveOptionsToFile();
}

void MenuWindow::updateUseBonusOptions(bool checked) {
    useBonusOptions = checked;
    saveOptionsToFile();
}



void MenuWindow::handleNbInvaderValueChanged(int value) {
    saveOptionsToFile();
    qDebug() << "Number of invaders changed to " << value;
}

void MenuWindow::openEditorWindow(const QString& type) {
    EditorWindow *editorWindow = new EditorWindow(this, type);
    connect(editorWindow, &EditorWindow::drawingSaved, this, &MenuWindow::handleDrawingSaved);
    editorWindow->show();
}

void MenuWindow::handleBackgroundButtonClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!imagePath.isEmpty()) {
        if (backgroundPixmapItem) {
            graphicsScene->removeItem(backgroundPixmapItem);
            delete backgroundPixmapItem;
        }
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            backgroundPixmapItem = graphicsScene->addPixmap(pixmap);
            graphicsView->fitInView(backgroundPixmapItem, Qt::KeepAspectRatio);
            layout->addWidget(graphicsView);
        }
    }
}

void MenuWindow::returnToMain() {
    emit MainButtonClicked();
}

void MenuWindow::openColorPickerWindow(QPushButton *button) {
    ColorPickerWindow *colorPickerWindow = new ColorPickerWindow(colors.toList(), this);
    if (colorPickerWindow->exec() == QDialog::Accepted) {
        QColor selectedColor = colorPickerWindow->getColor();
        colors = colorPickerWindow->getColors().toVector();
        if (button) {
            button->setStyleSheet(QString("background-color: %1").arg(selectedColor.name()));
        }
    }
    delete colorPickerWindow;
    saveOptionsToFile();
}

void MenuWindow::saveOptionsToFile() {
    qDebug() << "save options";
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
    QFile file(filePath);
    qDebug() << "File path:" << file.fileName();
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ListOfColors:";
        for (int i = 0; i < colors.size(); ++i) {
            if (i > 0)
                out << ",";
            out << colors[i].name();
        }
        out << "" << Qt::endl;
        out << "BulletColor:" << colorBulletButton->styleSheet().split(":").last().trimmed() << Qt::endl;
        out << "InvaderColor:" << colorInvaderButton->styleSheet().split(":").last().trimmed() << Qt::endl;
        out << "ShipColor:" << colorShipButton->styleSheet().split(":").last().trimmed() << Qt::endl;
        out << "PowerupColor:" << colorShipButton->styleSheet().split(":").last().trimmed() << Qt::endl;
        out << "NumberOfInvaders:" << nbInvaderSpinBox->value() << Qt::endl;
        out << "UseBonusOptions:" << useBonusOptions << Qt::endl;
        out << "InvaderSpacing:" << invaderSpacing << Qt::endl;
        out << "BulletSpeed:" << bulletSpeed << Qt::endl;
        out << "FireRate:" << fireRate << Qt::endl;
        out << "UpdateInterval:" << updateInterval << Qt::endl;
        file.close();
    } else {
        qDebug() << "Failed to open option file for writing.";
    }
}

void MenuWindow::loadOptionsFromFile() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/options";
    QDir().mkpath(QFileInfo(filePath).absoluteDir().path());
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        if (line.startsWith("ListOfColors:")) {
            QStringList colors = line.split(":").last().split(",");
            for (int i = 0; i < colors.size(); ++i) {
                this->colors.append(QColor(colors[i]));
            }
        }
        line = in.readLine();
        if (line.startsWith("BulletColor:")) {
            colorBulletButton->setStyleSheet(QString("background-color: %1").arg(line.split(":").last().trimmed()));
        }
        line = in.readLine();
        if (line.startsWith("InvaderColor:")) {
            colorInvaderButton->setStyleSheet(QString("background-color: %1").arg(line.split(":").last().trimmed()));
        }
        line = in.readLine();
        if (line.startsWith("ShipColor:")) {
            colorShipButton->setStyleSheet(QString("background-color: %1").arg(line.split(":").last().trimmed()));
        }
        line = in.readLine();
        if (line.startsWith("PowerupColor")){
            colorPowerupButton->setStyleSheet(QString("background-color: %1").arg(line.split(":").last().trimmed()));
        }
        line = in.readLine();
        if (line.startsWith("NumberOfInvaders:")) {
            nbInvaderSpinBox->setValue(line.split(":").last().toInt());
        }
        line = in.readLine();
        if (line.startsWith("UseBonusOptions:")) {
            useBonusOptions = line.split(":").last().toInt();
            useBonusOptionsCheckBox->setChecked(useBonusOptions);
        }
        line = in.readLine();
        if (line.startsWith("InvaderSpacing:")) {
            invaderSpacing = line.split(":").last().toInt();
            invaderSpacingSlider->setValue(invaderSpacing);
        }
        line = in.readLine();
        if (line.startsWith("BulletSpeed:")) {
            bulletSpeed = line.split(":").last().toInt();
            bulletSpeedSlider->setValue(bulletSpeed);
        }
        line = in.readLine();
        if (line.startsWith("FireRate:")) {
            fireRate = line.split(":").last().toInt();
            fireRateSlider->setValue(fireRate);
        }
        line = in.readLine();
        if (line.startsWith("UpdateInterval:")) {
            updateInterval = line.split(":").last().toInt();
            updateIntervalSlider->setValue(updateInterval);
        }
        file.close();
    } else {
        qDebug() << "Failed to open option file for reading.";
    }
}

void MenuWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed: " << event->key();
    if (event->key() == Qt::Key_Escape) {
        saveOptionsToFile();
        emit MainButtonClicked();
        qDebug() << "Escape";
    }
}

void MenuWindow::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Key released: " << event->key();
    if (event->key() == Qt::Key_Escape) {
        qDebug() << "Escape";
    }
}

MenuWindow::~MenuWindow() {
    saveOptionsToFile(); // Save options before destroying the window

    // Deleting allocated resources
    delete layout;
    delete bulletColorLayout;
    delete bulletColorLabel;
    delete colorBulletButton;
    delete invaderColorLayout;
    delete invaderColorLabel;
    delete powerupColorLabel;
    delete powerupColorLayout;
    delete powerupEditorButton;
    delete colorPowerupButton;
    delete colorInvaderButton;
    delete shipColorLayout;
    delete shipColorLabel;
    delete colorShipButton;
    delete nbInvaderLayout;
    delete nbInvaderSpinBox;
    delete backgroundButton;
    delete returnButton;

    if (backgroundPixmapItem) {
        graphicsScene->removeItem(backgroundPixmapItem);
        delete backgroundPixmapItem;
    }
    delete graphicsView;
    delete graphicsScene;
}
