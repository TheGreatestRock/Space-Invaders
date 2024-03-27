#include "editorwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include <QPushButton>
#include <QLayout>

EditorWindow::EditorWindow(QWidget *parent, QString saveFileName) : QDialog(parent), saveFileName(saveFileName)
{
    grid = QVector<QVector<bool>>(gridSize, QVector<bool>(gridSize, false));
    setMinimumSize(300, 350);
    //name of the window
    setWindowTitle(saveFileName + " Editor");
    // Add a save button to the dialog
    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &EditorWindow::saveToFile);

    // Set the layout of the dialog
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(saveButton, Qt::AlignBottom);
    layout->addWidget(saveButton, Qt::AlignBottom);
}

void EditorWindow::mousePressEvent(QMouseEvent *event)
{
    int cellSize = qMin(width() / gridSize, height() / gridSize);
    int x = event->x() / cellSize;
    int y = event->y() / cellSize;

    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize)
        return;
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
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + saveFileName;
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
        emit drawingSaved(grid);
    }
}
