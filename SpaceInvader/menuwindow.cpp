// menuwindow.cpp
#include "menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    colorBulletButton = new QPushButton("Choose Bullet Color", this);
    colorInvaderButton = new QPushButton("Choose Invader Color", this);
    colorShipButton = new QPushButton("Choose Ship Color", this);
    nbInvaderSpinBox = new QSpinBox(this);
    nbInvaderSpinBox->setRange(1, 100);

    connect(colorBulletButton, &QPushButton::clicked, this, &MenuWindow::handleColorBulletButtonClicked);
    connect(colorInvaderButton, &QPushButton::clicked, this, &MenuWindow::handleColorInvaderButtonClicked);
    connect(colorShipButton, &QPushButton::clicked, this, &MenuWindow::handleColorShipButtonClicked);
    connect(nbInvaderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuWindow::handleNbInvaderValueChanged);

    layout->addWidget(colorBulletButton);
    layout->addWidget(colorInvaderButton);
    layout->addWidget(colorShipButton);
    layout->addWidget(nbInvaderSpinBox);
    setLayout(layout);
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::handleColorBulletButtonClicked() {
    openColorPickerWindow();
}

void MenuWindow::handleColorInvaderButtonClicked() {
    openColorPickerWindow();
}

void MenuWindow::handleColorShipButtonClicked() {
    openColorPickerWindow();
}

void MenuWindow::handleNbInvaderValueChanged(int value) {
    qDebug() << "Nb Invader Value Changed: " << value;
}


void MenuWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed: " << event->key();
    if (event->key() == Qt::Key_Escape) {
        emit goToMenu();
        qDebug() << "Escape";
    }
}

void MenuWindow::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Key released: " << event->key();
    if (event->key() == Qt::Key_Escape) {
        qDebug() << "Escape";
    }
}

void MenuWindow::openColorPickerWindow() {
    ColorPickerWindow *colorPickerWindow = new ColorPickerWindow(this);
    if (colorPickerWindow->exec() == QDialog::Accepted) {
        // Color selected, update corresponding button color
        QColor selectedColor = colorPickerWindow->getColor();
        QObject *senderButton = sender(); // Get the button that triggered the event
        if (senderButton == colorBulletButton) {
            colorBulletButton->setStyleSheet(QString("background-color: %1").arg(selectedColor.name()));
        } else if (senderButton == colorInvaderButton) {
            colorInvaderButton->setStyleSheet(QString("background-color: %1").arg(selectedColor.name()));
        } else if (senderButton == colorShipButton) {
            colorShipButton->setStyleSheet(QString("background-color: %1").arg(selectedColor.name()));
        }
    }
    delete colorPickerWindow;
}
