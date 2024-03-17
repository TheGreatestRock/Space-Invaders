// colorpickerwindow.h
#ifndef COLORPICKERWINDOW_H
#define COLORPICKERWINDOW_H

#include <QDialog>
#include <QColor>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColorDialog>

class ColorPickerWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ColorPickerWindow(QWidget *parent = nullptr);
    QList<QColor> getColors() const;
    QColor getColor() const;

signals:
    void colorsSelected(const QList<QColor> &selectedColors);

private slots:
    void selectColor();
    void addColor();

private:
    QListWidget *colorListWidget;
    QPushButton *selectColorButton;
    QPushButton *addColorButton;
    QColorDialog *colorDialog;

    QList<QColor> colors;
};

#endif // COLORPICKERWINDOW_H
