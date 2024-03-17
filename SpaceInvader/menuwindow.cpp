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
    nbInvaderSpinBox->setRange(1, 10);
    nbInvaderSpinBox->setValue(5);
    nbInvaderLayout->addWidget(nbInvaderLabel);
    nbInvaderLayout->addWidget(nbInvaderSpinBox);

    returnButton = new QPushButton("Return to Main", this);

    connect(colorBulletButton, &QPushButton::clicked, this, &MenuWindow::handleColorBulletButtonClicked);
    connect(colorInvaderButton, &QPushButton::clicked, this, &MenuWindow::handleColorInvaderButtonClicked);
    connect(colorShipButton, &QPushButton::clicked, this, &MenuWindow::handleColorShipButtonClicked);
    connect(nbInvaderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuWindow::handleNbInvaderValueChanged);
    connect(returnButton, &QPushButton::clicked, this, &MenuWindow::returnToMain); // Connect the return button to the new slot

    layout->addLayout(bulletColorLayout);
    layout->addLayout(invaderColorLayout);
    layout->addLayout(shipColorLayout);
    layout->addLayout(nbInvaderLayout);
    layout->addWidget(returnButton);
    setLayout(layout);
}

MenuWindow::~MenuWindow() {
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
}

void MenuWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed: " << event->key();
    if (event->key() == Qt::Key_Escape) {
        emit goToMain();
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
}

void MenuWindow::returnToMain() {
    emit goToMain();
}
