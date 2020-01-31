/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "rvwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    RVWidget *widgetRV;
    QVBoxLayout *verticalLayout;
    QPushButton *animationButton;
    QFrame *line_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QDial *fov;
    QFrame *line;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox;
    QLabel *label_2;
    QSlider *opacitySlider;
    QLabel *label_3;
    QSlider *horizontalSlider;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetRV = new RVWidget(centralwidget);
        widgetRV->setObjectName(QString::fromUtf8("widgetRV"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetRV->sizePolicy().hasHeightForWidth());
        widgetRV->setSizePolicy(sizePolicy);
        widgetRV->setMinimumSize(QSize(400, 300));

        horizontalLayout->addWidget(widgetRV);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        animationButton = new QPushButton(centralwidget);
        animationButton->setObjectName(QString::fromUtf8("animationButton"));
#ifndef QT_NO_TOOLTIP
        animationButton->setToolTip(QString::fromUtf8("Activer l'animation"));
#endif // QT_NO_TOOLTIP
        animationButton->setCheckable(true);

        verticalLayout->addWidget(animationButton);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        fov = new QDial(groupBox_2);
        fov->setObjectName(QString::fromUtf8("fov"));
        fov->setMinimum(2);
        fov->setMaximum(120);
        fov->setPageStep(5);
        fov->setValue(45);
        fov->setTracking(true);
        fov->setNotchTarget(5.000000000000000);
        fov->setNotchesVisible(true);

        verticalLayout_3->addWidget(fov);


        verticalLayout->addWidget(groupBox_2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_2->addWidget(checkBox);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        opacitySlider = new QSlider(groupBox);
        opacitySlider->setObjectName(QString::fromUtf8("opacitySlider"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(opacitySlider->sizePolicy().hasHeightForWidth());
        opacitySlider->setSizePolicy(sizePolicy1);
        opacitySlider->setMaximum(100);
        opacitySlider->setValue(100);
        opacitySlider->setOrientation(Qt::Horizontal);
        opacitySlider->setTickPosition(QSlider::TicksBothSides);
        opacitySlider->setTickInterval(10);

        verticalLayout_2->addWidget(opacitySlider);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setMaximum(400);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(animationButton, SIGNAL(clicked()), widgetRV, SLOT(startAnimation()));
        QObject::connect(fov, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeFov(int)));
        QObject::connect(opacitySlider, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeOpacity(int)));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), widgetRV, SLOT(changeWireFrame(bool)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeScale(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
#ifndef QT_NO_TOOLTIP
        widgetRV->setToolTip(QApplication::translate("MainWindow", "Utiliser la souris pour bouger le cube", nullptr));
#endif // QT_NO_TOOLTIP
        animationButton->setText(QApplication::translate("MainWindow", "Animation", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "R\303\251glages cam\303\251ra", nullptr));
        label->setText(QApplication::translate("MainWindow", "Ouverture focale", nullptr));
#ifndef QT_NO_TOOLTIP
        fov->setToolTip(QApplication::translate("MainWindow", "Change la focale de la cam\303\251ra", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "R\303\251glages objet", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Fil de fer", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Opacit\303\251", nullptr));
#ifndef QT_NO_TOOLTIP
        opacitySlider->setToolTip(QApplication::translate("MainWindow", "Modfie l'opacit\303\251", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "Taille", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
