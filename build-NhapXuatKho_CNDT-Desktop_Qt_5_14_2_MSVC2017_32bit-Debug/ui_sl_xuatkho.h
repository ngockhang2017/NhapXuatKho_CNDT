/********************************************************************************
** Form generated from reading UI file 'sl_xuatkho.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SL_XUATKHO_H
#define UI_SL_XUATKHO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SL_XuatKho
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SL_XuatKho)
    {
        if (SL_XuatKho->objectName().isEmpty())
            SL_XuatKho->setObjectName(QString::fromUtf8("SL_XuatKho"));
        SL_XuatKho->resize(505, 211);
        centralwidget = new QWidget(SL_XuatKho);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Palatino Linotype"));
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Palatino Linotype"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        spinBox->setFont(font1);

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(286, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton->setFont(font2);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Palatino Linotype"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_2->setFont(font3);

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_2);

        SL_XuatKho->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SL_XuatKho);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 505, 25));
        SL_XuatKho->setMenuBar(menubar);
        statusbar = new QStatusBar(SL_XuatKho);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SL_XuatKho->setStatusBar(statusbar);

        retranslateUi(SL_XuatKho);

        QMetaObject::connectSlotsByName(SL_XuatKho);
    } // setupUi

    void retranslateUi(QMainWindow *SL_XuatKho)
    {
        SL_XuatKho->setWindowTitle(QCoreApplication::translate("SL_XuatKho", "X\303\241c nh\341\272\255n s\341\273\221 l\306\260\341\273\243ng", nullptr));
        label->setText(QCoreApplication::translate("SL_XuatKho", "Nh\341\272\255p s\341\273\221 l\306\260\341\273\243ng xu\341\272\245t kho:", nullptr));
        pushButton->setText(QCoreApplication::translate("SL_XuatKho", "X\303\241c nh\341\272\255n", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SL_XuatKho", "H\341\273\247y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SL_XuatKho: public Ui_SL_XuatKho {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SL_XUATKHO_H
