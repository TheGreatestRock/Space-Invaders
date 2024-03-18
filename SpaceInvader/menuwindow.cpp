// menuwindow.cpp
#include "menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    bulletColorLayout = new QHBoxLayout();
    bulletColorLabel = new QLabel("Bullet Color:", this);
    colorBulletButton = new QPushButton("Change color", this);
    bulletColorLayout->addWidget(bulletColorLabel);
    bulletColorLayout->addWidget(colorBulletButton);

    invaderColorLayout = new QHBoxLayout();
    invaderColorLabel = new QLabel("Invader Color:", this);
    colorInvaderButton = new QPushButton("Change color", this);
    invaderColorLayout->addWidget(invaderColorLabel);
    invaderColorLayout->addWidget(colorInvaderButton);

    shipColorLayout = new QHBoxLayout();
    shipColorLabel = new QLabel("Ship Color:", this);
    colorShipButton = new QPushButton("Change color", this);
    shipColorLayout->addWidget(shipColorLabel);
    shipColorLayout->addWidget(colorShipButton);

    nbInvaderLayout = new QHBoxLayout();
    QLabel *nbInvaderLabel = new QLabel("Number of Invader:", this);
    nbInvaderSpinBox = new QSpinBox(this);
    nbInvaderSpinBox->setRange(1, 100);
    nbInvaderSpinBox->setValue(5);
    nbInvaderLayout->addWidget(nbInvaderLabel);
    nbInvaderLayout->addWidget(nbInvaderSpinBox);

    returnButton = new QPushButton("Return to Main", this);

    connect(colorBulletButton, &QPushButton::clicked, this, &MenuWindow::handleColorBulletButtonClicked);
    connect(colorInvaderButton, &QPushButton::clicked, this, &MenuWindow::handleColorInvaderButtonClicked);
    connect(colorShipButton, &QPushButton::clicked, this, &MenuWindow::handleColorShipButtonClicked);
    connect(nbInvaderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuWindow::handleNbInvaderValueChanged);
    connect(returnButton, &QPushButton::clicked, this, &MenuWindow::returnToMain);

    layout->addLayout(bulletColorLayout);
    layout->addLayout(invaderColorLayout);
    layout->addLayout(shipColorLayout);
    layout->addLayout(nbInvaderLayout);
    layout->addWidget(returnButton);
    setLayout(layout);

    loadOptionsFromFile();
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

void MenuWindow::handleNbInvaderValueChanged(int value) {
    qDebug() << "Nb Invader Value Changed: " << value;
    saveOptionsToFile();
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

void MenuWindow::returnToMain() {
    emit MainButtonClicked();
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
        out << "NumberOfInvaders:" << nbInvaderSpinBox->value() << Qt::endl;
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
        if (line.startsWith("NumberOfInvaders:")) {
            nbInvaderSpinBox->setValue(line.split(":").last().toInt());
        }
        file.close();
    } else {
        qDebug() << "Failed to open option file for reading.";
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
    delete colorInvaderButton;
    delete shipColorLayout;
    delete shipColorLabel;
    delete colorShipButton;
    delete nbInvaderLayout;
    delete nbInvaderSpinBox;
    delete returnButton;
}
