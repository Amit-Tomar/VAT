/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollBar *ScaleBar;
    QHBoxLayout *horizontalLayout_4;
    QScrollBar *TranslateBarX;
    QScrollBar *TranslateBarY;
    QHBoxLayout *horizontalLayout;
    QScrollBar *RotateBarX;
    QScrollBar *RorateBarY;
    QScrollBar *RotateBarZ;
    QCheckBox *Bernstein;
    QCheckBox *Casteljau;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *topMessage;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 800);
        verticalLayoutWidget = new QWidget(MainWindow);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(230, 620, 551, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ScaleBar = new QScrollBar(verticalLayoutWidget);
        ScaleBar->setObjectName(QStringLiteral("ScaleBar"));
        ScaleBar->setMinimum(1);
        ScaleBar->setMaximum(100);
        ScaleBar->setValue(1);
        ScaleBar->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(ScaleBar);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        TranslateBarX = new QScrollBar(verticalLayoutWidget);
        TranslateBarX->setObjectName(QStringLiteral("TranslateBarX"));
        TranslateBarX->setValue(50);
        TranslateBarX->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(TranslateBarX);

        TranslateBarY = new QScrollBar(verticalLayoutWidget);
        TranslateBarY->setObjectName(QStringLiteral("TranslateBarY"));
        TranslateBarY->setValue(50);
        TranslateBarY->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(TranslateBarY);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        RotateBarX = new QScrollBar(verticalLayoutWidget);
        RotateBarX->setObjectName(QStringLiteral("RotateBarX"));
        RotateBarX->setValue(0);
        RotateBarX->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(RotateBarX);

        RorateBarY = new QScrollBar(verticalLayoutWidget);
        RorateBarY->setObjectName(QStringLiteral("RorateBarY"));
        RorateBarY->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(RorateBarY);

        RotateBarZ = new QScrollBar(verticalLayoutWidget);
        RotateBarZ->setObjectName(QStringLiteral("RotateBarZ"));
        RotateBarZ->setMaximum(360);
        RotateBarZ->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(RotateBarZ);


        verticalLayout->addLayout(horizontalLayout);

        Bernstein = new QCheckBox(MainWindow);
        Bernstein->setObjectName(QStringLiteral("Bernstein"));
        Bernstein->setGeometry(QRect(10, 630, 101, 21));
        Casteljau = new QCheckBox(MainWindow);
        Casteljau->setObjectName(QStringLiteral("Casteljau"));
        Casteljau->setGeometry(QRect(10, 660, 111, 21));
        label = new QLabel(MainWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 630, 57, 15));
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 660, 81, 16));
        label_3 = new QLabel(MainWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 690, 57, 15));
        topMessage = new QLabel(MainWindow);
        topMessage->setObjectName(QStringLiteral("topMessage"));
        topMessage->setGeometry(QRect(0, 600, 791, 21));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MT2013008_Assignment1", 0));
        Bernstein->setText(QApplication::translate("MainWindow", "Bernstein", 0));
        Casteljau->setText(QApplication::translate("MainWindow", "Casteljau", 0));
        label->setText(QApplication::translate("MainWindow", "Scale", 0));
        label_2->setText(QApplication::translate("MainWindow", "Translate", 0));
        label_3->setText(QApplication::translate("MainWindow", "Rotate", 0));
        topMessage->setText(QApplication::translate("MainWindow", "   Click on the surface to draw curves. Use bottom options to change algorithm or  perform scale/rotation/translation.                      ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
