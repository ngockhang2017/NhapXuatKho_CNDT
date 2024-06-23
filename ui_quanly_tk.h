/********************************************************************************
** Form generated from reading UI file 'quanly_tk.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUANLY_TK_H
#define UI_QUANLY_TK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuanLy_TK
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_20;
    QWidget *widget_13;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_9;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QuanLy_TK)
    {
        if (QuanLy_TK->objectName().isEmpty())
            QuanLy_TK->setObjectName(QString::fromUtf8("QuanLy_TK"));
        QuanLy_TK->resize(984, 577);
        centralwidget = new QWidget(QuanLy_TK);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_8 = new QHBoxLayout(widget_4);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_20 = new QSpacerItem(131, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_20);

        widget_13 = new QWidget(widget_4);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        widget_13->setStyleSheet(QString::fromUtf8("border-image: url(:/images/images/images-removebg-preview.png);"));

        horizontalLayout_8->addWidget(widget_13);

        horizontalLayout_8->setStretch(0, 2);
        horizontalLayout_8->setStretch(1, 3);

        horizontalLayout->addWidget(widget_4);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, 200, -1);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("Palatino Linotype"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Palatino Linotype"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);


        horizontalLayout->addWidget(widget_5);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);

        verticalLayout->addWidget(widget_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font2;
        font2.setPointSize(10);
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_5);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableWidget = new QTableWidget(widget_2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout_2->addWidget(tableWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        lineEdit_3 = new QLineEdit(widget_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 3, 1, 1, 1);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 5, 1, 1, 1);

        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 5, 0, 1, 1);

        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        comboBox = new QComboBox(widget_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_4->addWidget(widget_2);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 10);

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 8);
        QuanLy_TK->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QuanLy_TK);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 984, 20));
        QuanLy_TK->setMenuBar(menubar);
        statusbar = new QStatusBar(QuanLy_TK);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QuanLy_TK->setStatusBar(statusbar);

        retranslateUi(QuanLy_TK);

        QMetaObject::connectSlotsByName(QuanLy_TK);
    } // setupUi

    void retranslateUi(QMainWindow *QuanLy_TK)
    {
        QuanLy_TK->setWindowTitle(QCoreApplication::translate("QuanLy_TK", "Qu\341\272\243n l\303\275 t\303\240i kho\341\272\243n", nullptr));
        label_3->setText(QCoreApplication::translate("QuanLy_TK", "B\341\273\230 M\303\224N C\303\224NG NGH\341\273\206 \304\220I\341\273\206N T\341\273\254", nullptr));
        label_4->setText(QCoreApplication::translate("QuanLy_TK", "PH\341\272\246N M\341\273\200M QU\341\272\242N L\303\235 KHO", nullptr));
        label_5->setText(QCoreApplication::translate("QuanLy_TK", "QU\341\272\242N L\303\235 T\303\200I KHO\341\272\242N \304\220\304\202NG NH\341\272\254P", nullptr));
        label_8->setText(QCoreApplication::translate("QuanLy_TK", "Quy\341\273\201n truy c\341\272\255p:", nullptr));
        label_6->setText(QCoreApplication::translate("QuanLy_TK", "T\303\252n t\303\240i kho\341\272\243n:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("QuanLy_TK", "L\306\260u t\303\240i kho\341\272\243n m\341\273\233i", nullptr));
        label_7->setText(QCoreApplication::translate("QuanLy_TK", "M\341\272\255t kh\341\272\251u:", nullptr));
        pushButton->setText(QCoreApplication::translate("QuanLy_TK", "C\341\272\255p nh\341\272\255t th\303\264ng tin", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QuanLy_TK", "X\303\263a t\303\240i kho\341\272\243n n\303\240y", nullptr));
        pushButton_3->setText(QCoreApplication::translate("QuanLy_TK", "B\341\272\257t \304\221\341\272\247u c\341\272\245p t\303\240i kho\341\272\243n m\341\273\233i", nullptr));
        label_9->setText(QCoreApplication::translate("QuanLy_TK", "L\341\273\215c:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("QuanLy_TK", "Admin", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("QuanLy_TK", "Qu\341\272\243n l\303\275 kho", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("QuanLy_TK", "K\341\273\271 thu\341\272\255t vi\303\252n", nullptr));

    } // retranslateUi

};

namespace Ui {
    class QuanLy_TK: public Ui_QuanLy_TK {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUANLY_TK_H
