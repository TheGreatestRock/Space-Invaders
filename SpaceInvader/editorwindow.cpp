#include "editorwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>

EditorWindow::EditorWindow(QWidget *parent) : QWidget(parent)
{
    grid = QVector<QVector<bool>>(gridSize, QVector<bool>(gridSize, false));
}

void EditorWindow::mousePressEvent(QMouseEvent *event)
{
    int cellSize = qMin(width() / gridSize, height() / gridSize);
    int x = event->x() / cellSize;
    int y = event->y() / cellSize;

    grid[y][x] = !grid[y][x];

    update();
}

void EditorWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int cellSize = qMin(width() / gridSize, height() / gridSize);

    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            QRect cellRect(x * cellSize, y * cellSize, cellSize, cellSize);
            painter.fillRect(cellRect, grid[y][x] ? Qt::white : Qt::black);
            painter.drawRect(cellRect);
        }
    }
}

void EditorWindow::saveToFile()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/drawing.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (int y = 0; y < gridSize; ++y) {
            for (int x = 0; x < gridSize; ++x) {
                out << (grid[y][x] ? "1" : "0") << " ";
            }
            out << Qt::endl;
        }
        file.close();
    }
}
