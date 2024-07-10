/********************************************************************************
** Form generated from reading UI file 'tk_canhan.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TK_CANHAN_H
#define UI_TK_CANHAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TK_CaNhan
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_mk;
    QLabel *label_2;
    QLineEdit *lineEdit_tenTK;
    QLabel *label;
    QLineEdit *lineEdit_Quyen;
    QLabel *label_3;
    QPushButton *pushButton_luu;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TK_CaNhan)
    {
        if (TK_CaNhan->objectName().isEmpty())
            TK_CaNhan->setObjectName(QString::fromUtf8("TK_CaNhan"));
        TK_CaNhan->resize(587, 288);
        centralwidget = new QWidget(TK_CaNhan);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));

        horizontalLayout->addWidget(widget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_mk = new QLineEdit(centralwidget);
        lineEdit_mk->setObjectName(QString::fromUtf8("lineEdit_mk"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lineEdit_mk->setFont(font);

        gridLayout->addWidget(lineEdit_mk, 2, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_tenTK = new QLineEdit(centralwidget);
        lineEdit_tenTK->setObjectName(QString::fromUtf8("lineEdit_tenTK"));
        QFont font1;
        font1.setItalic(true);
        lineEdit_tenTK->setFont(font1);
        lineEdit_tenTK->setReadOnly(true);

        gridLayout->addWidget(lineEdit_tenTK, 0, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_Quyen = new QLineEdit(centralwidget);
        lineEdit_Quyen->setObjectName(QString::fromUtf8("lineEdit_Quyen"));
        lineEdit_Quyen->setFont(font1);
        lineEdit_Quyen->setReadOnly(true);

        gridLayout->addWidget(lineEdit_Quyen, 1, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButton_luu = new QPushButton(centralwidget);
        pushButton_luu->setObjectName(QString::fromUtf8("pushButton_luu"));
        pushButton_luu->setFont(font);

        gridLayout->addWidget(pushButton_luu, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 3);
        TK_CaNhan->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TK_CaNhan);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 587, 25));
        TK_CaNhan->setMenuBar(menubar);
        statusbar = new QStatusBar(TK_CaNhan);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TK_CaNhan->setStatusBar(statusbar);

        retranslateUi(TK_CaNhan);

        QMetaObject::connectSlotsByName(TK_CaNhan);
    } // setupUi

    void retranslateUi(QMainWindow *TK_CaNhan)
    {
        TK_CaNhan->setWindowTitle(QCoreApplication::translate("TK_CaNhan", "Qu\341\272\243n l\303\275 t\303\240i kho\341\272\243n c\303\241 nh\303\242n", nullptr));
        label_2->setText(QCoreApplication::translate("TK_CaNhan", "Quy\341\273\201n truy c\341\272\255p:", nullptr));
        label->setText(QCoreApplication::translate("TK_CaNhan", "T\303\252n t\303\240i kho\341\272\243n (kh\303\264ng \304\221\341\273\225i):", nullptr));
        label_3->setText(QCoreApplication::translate("TK_CaNhan", "M\341\272\255t kh\341\272\251u:", nullptr));
        pushButton_luu->setText(QCoreApplication::translate("TK_CaNhan", "L\306\260u m\341\272\255t kh\341\272\251u m\341\273\233i \304\221\303\243 nh\341\272\255p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TK_CaNhan: public Ui_TK_CaNhan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TK_CANHAN_H
