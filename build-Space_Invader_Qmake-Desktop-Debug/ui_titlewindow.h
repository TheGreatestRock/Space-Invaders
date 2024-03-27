/********************************************************************************
** Form generated from reading UI file 'titlewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEWINDOW_H
#define UI_TITLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QLabel *titleLabel;
    QHBoxLayout *hboxLayout;
    QLabel *highScoreLabel;
    QLabel *highScoreValue;
    QPushButton *playButton;
    QPushButton *menuButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(titleLabel);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        highScoreLabel = new QLabel(centralwidget);
        highScoreLabel->setObjectName(QString::fromUtf8("highScoreLabel"));

        hboxLayout->addWidget(highScoreLabel);

        highScoreValue = new QLabel(centralwidget);
        highScoreValue->setObjectName(QString::fromUtf8("highScoreValue"));

        hboxLayout->addWidget(highScoreValue);


        vboxLayout->addLayout(hboxLayout);

        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));

        vboxLayout->addWidget(playButton);

        menuButton = new QPushButton(centralwidget);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));

        vboxLayout->addWidget(menuButton);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        vboxLayout->addWidget(exitButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Space Invader QT", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Space Invader QT", nullptr));
        highScoreLabel->setText(QCoreApplication::translate("MainWindow", "High Score:", nullptr));
        highScoreValue->setText(QCoreApplication::translate("MainWindow", "10000", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        menuButton->setText(QCoreApplication::translate("MainWindow", "Options", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEWINDOW_H
