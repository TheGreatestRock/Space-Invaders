// menuwindow.cpp
#include "menuwindow.h"
#include <QGraphicsItem>

MenuWindow::MenuWindow(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    bulletColorLayout = new QHBoxLayout();
    bulletColorLabel = new QLabel("Bullet Color:", this);
    colorBulletButton = new QPushButton("Change color", this);
    bulletEditorButton = new QPushButton("Bullet Editor", this);
    bulletColorLayout->addWidget(bulletColorLabel);
    bulletColorLayout->addWidget(colorBulletButton);
    bulletColorLayout->addWidget(bulletEditorButton);

    invaderEditorButton = new QPushButton("Invader Editor", this);
    invaderColorLayout = new QHBoxLayout();
    invaderColorLabel = new QLabel("Invader Color:", this);
    colorInvaderButton = new QPushButton("Change color", this);
    invaderColorLayout->addWidget(invaderColorLabel);
    invaderColorLayout->addWidget(colorInvaderButton);
    invaderColorLayout->addWidget(invaderEditorButton);

    shipColorLayout = new QHBoxLayout();
    shipColorLabel = new QLabel("Ship Color:", this);
    colorShipButton = new QPushButton("Change color", this);
    shipEditorButton = new QPushButton("Ship Editor", this);
    shipColorLayout->addWidget(shipColorLabel);
    shipColorLayout->addWidget(colorShipButton);
    shipColorLayout->addWidget(shipEditorButton);

    nbInvaderLayout = new QHBoxLayout();
    QLabel *nbInvaderLabel = new QLabel("Number of Invader:", this);
    nbInvaderSpinBox = new QSpinBox(this);
    nbInvaderSpinBox->setRange(1, 100);
    nbInvaderSpinBox->setValue(5);
    nbInvaderLayout->addWidget(nbInvaderLabel);
    nbInvaderLayout->addWidget(nbInvaderSpinBox);

    backgroundButton = new QPushButton("Background", this);
    returnButton = new QPushButton("Return to Main", this);

    connect(colorBulletButton, &QPushButton::clicked, this, &MenuWindow::handleColorBulletButtonClicked);
    connect(colorInvaderButton, &QPushButton::clicked, this, &MenuWindow::handleColorInvaderButtonClicked);
    connect(colorShipButton, &QPushButton::clicked, this, &MenuWindow::handleColorShipButtonClicked);
    connect(nbInvaderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuWindow::handleNbInvaderValueChanged);
    connect(returnButton, &QPushButton::clicked, this, &MenuWindow::returnToMain);
    connect(backgroundButton, &QPushButton::clicked, this, &MenuWindow::handleBackgroundButtonClicked);
    connect(shipEditorButton, &QPushButton::clicked, this, &MenuWindow::handleShipEditorButtonClicked);
    connect(invaderEditorButton, &QPushButton::clicked, this, &MenuWindow::handleInvaderEditorButtonClicked);
    connect(bulletEditorButton, &QPushButton::clicked, this, &MenuWindow::handleBulletEditorButtonClicked);


    layout->addLayout(bulletColorLayout);
    layout->addLayout(invaderColorLayout);
    layout->addLayout(shipColorLayout);
    layout->addLayout(nbInvaderLayout);
    layout->addWidget(backgroundButton);
    layout->addWidget(returnButton);
    setLayout(layout);

    loadOptionsFromFile();

    graphicsScene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(graphicsScene);
    backgroundPixmapItem = nullptr;
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

void MenuWindow::handleShipEditorButtonClicked() {
    openEditorWindow("Ship");
}

void MenuWindow::handleInvaderEditorButtonClicked() {
    openEditorWindow("Invader");
}

void MenuWindow::handleBulletEditorButtonClicked() {
    openEditorWindow("Bullet");
}

void MenuWindow::handleDrawingSaved(const QVector<QVector<bool>>& grid)
{
    qDebug() << "Drawing saved";
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j]) {
                QGraphicsRectItem *rect = graphicsScene->addRect(j * 10, i * 10, 10, 10, QPen(Qt::black), QBrush(Qt::black));
            }
        }
    }
}

void MenuWindow::handleNbInvaderValueChanged(int value) {
    saveOptionsToFile();
    qDebug() << "Number of invaders changed to " << value;
}

void MenuWindow::openEditorWindow(const QString& type) {
    EditorWindow *editorWindow = new EditorWindow(this, type);
    connect(editorWindow, &EditorWindow::drawingSaved, this, &MenuWindow::handleDrawingSaved);
    editorWindow->show();
}

void MenuWindow::handleBackgroundButtonClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!imagePath.isEmpty()) {
        if (backgroundPixmapItem) {
            graphicsScene->removeItem(backgroundPixmapItem);
            delete backgroundPixmapItem;
        }
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            backgroundPixmapItem = graphicsScene->addPixmap(pixmap);
            graphicsView->fitInView(backgroundPixmapItem, Qt::KeepAspectRatio);
            layout->addWidget(graphicsView);
        }
    }
}

void MenuWindow::returnToMain() {
    emit MainButtonClicked();
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
    delete backgroundButton;
    delete returnButton;

    if (backgroundPixmapItem) {
        graphicsScene->removeItem(backgroundPixmapItem);
        delete backgroundPixmapItem;
    }
    delete graphicsView;
    delete graphicsScene;
}
