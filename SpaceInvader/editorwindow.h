#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QDialog>
#include <QVector>

class EditorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = nullptr, QString saveFileName = "drawing.txt");

signals:
    void drawingSaved(const QVector<QVector<bool>> &grid);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void saveToFile();

private:
    static const int gridSize = 10;
    QVector<QVector<bool>> grid;
    QString saveFileName;
};

#endif // EDITORWINDOW_H
