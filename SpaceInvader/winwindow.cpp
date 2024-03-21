// winwindow.cpp
#include "winwindow.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>
#include <QStyle>
#include <QScreen>

WinWindow::WinWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    winLabel = new QLabel("You win", this);
    scoreLabel = new QLabel("Score: ", this);
    copyButton = new QPushButton("Copy to Clipboard", this);

    QFont labelFont("Papyrus", 16);
    winLabel->setFont(labelFont);
    scoreLabel->setFont(labelFont);

    winLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setAlignment(Qt::AlignCenter);

    winLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    scoreLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    layout->addWidget(winLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(copyButton);

    // Center the window on the screen
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(400, 300), // Set window size to 400x300
            qApp->primaryScreen()->availableGeometry()
            )
        );

    setLayout(layout);

    connect(copyButton, &QPushButton::clicked, this, &WinWindow::copyToClipboard);
}

void WinWindow::setScore(int score)
{
    scoreLabel->setText("Score: " + QString::number(score));
}

void WinWindow::copyToClipboard()
{
    QString textToCopy = scoreLabel->text() + "\n" ;
    QApplication::clipboard()->setText(textToCopy);
}
