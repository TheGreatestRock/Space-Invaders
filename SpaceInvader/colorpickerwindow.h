#ifndef COLORPICKERWINDOW_H
#define COLORPICKERWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QDebug>
#include <QListWidgetItem>

class ColorPickerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPickerWindow(const QList<QColor> &initialColors = QList<QColor>(), QWidget *parent = nullptr);
    QList<QColor> getColors() const;
    QColor getColor() const;

signals:
    void colorsSelected(const QList<QColor> &colors);

private slots:
    void selectColor();
    void addColor();
    void updateSelectColorButton();

private:
    QList<QColor> colors;
    QListWidget *colorListWidget;
    QPushButton *selectColorButton;
    QPushButton *addColorButton;
    QColorDialog *colorDialog;
};

#endif // COLORPICKERWINDOW_H
