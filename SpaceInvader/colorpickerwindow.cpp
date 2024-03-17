#include "colorpickerwindow.h"

ColorPickerWindow::ColorPickerWindow(QWidget *parent) : QDialog(parent)
{
    qDebug() << "ColorPickerWindow constructor called";
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

    // Connect signal for enabling/disabling selectColorButton
    connect(colorListWidget, &QListWidget::itemSelectionChanged, this, &ColorPickerWindow::updateSelectColorButton);

    // Initially, disable selectColorButton
    selectColorButton->setEnabled(false);
}

QList<QColor> ColorPickerWindow::getColors() const
{
    qDebug() << "getColors() called";
    return colors;
}

void ColorPickerWindow::selectColor()
{
    qDebug() << "selectColor() called";
    emit colorsSelected(colors);
    accept();
}

QColor ColorPickerWindow::getColor() const
{
    qDebug() << "getColor() called";
    QListWidgetItem *selectedItem = colorListWidget->currentItem();
    if (selectedItem) {
        QVariant variant = selectedItem->data(Qt::UserRole);
        QColor color = variant.value<QColor>();
        qDebug() << "Selected color =" << color;
        return color;
    }
    qDebug() << "No color selected";
    return QColor(); // Return a default color if no color is selected
}

void ColorPickerWindow::addColor()
{
    qDebug() << "addColor() called";
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        colors.append(color);
        QListWidgetItem *item = new QListWidgetItem(color.name(), colorListWidget);
        item->setBackground(color);
        QVariant variant;
        variant.setValue(color);
        item->setData(Qt::UserRole, variant);
    }
}

void ColorPickerWindow::updateSelectColorButton()
{
    // Enable selectColorButton if an item is selected, otherwise disable it
    selectColorButton->setEnabled(colorListWidget->selectedItems().size() > 0);
}
