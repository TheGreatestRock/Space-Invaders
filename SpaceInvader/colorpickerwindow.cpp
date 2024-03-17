// colorpickerwindow.cpp
#include "colorpickerwindow.h"

ColorPickerWindow::ColorPickerWindow(QWidget *parent) : QDialog(parent)
{
    colorListWidget = new QListWidget(this);
    selectColorButton = new QPushButton("Select Color", this);
    addColorButton = new QPushButton("Add Color", this);
    colorDialog = new QColorDialog(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(selectColorButton);
    buttonLayout->addWidget(addColorButton);
    mainLayout->addWidget(colorListWidget);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(selectColorButton, &QPushButton::clicked, this, &ColorPickerWindow::selectColor);
    connect(addColorButton, &QPushButton::clicked, this, &ColorPickerWindow::addColor);
}

QList<QColor> ColorPickerWindow::getColors() const
{
    return colors;
}

void ColorPickerWindow::selectColor()
{
    emit colorsSelected(colors);
    accept();
}

QColor ColorPickerWindow::getColor() const
{
    return colorDialog->currentColor(); 
}

void ColorPickerWindow::addColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        colors.append(color);
        QListWidgetItem *item = new QListWidgetItem(color.name(), colorListWidget);
        item->setBackground(color);
    }
}
