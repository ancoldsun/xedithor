/********************************************************************************
** Form generated from reading UI file 'toolDialog.ui'
**
** Created: Sun Jan 22 22:48:58 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLDIALOG_H
#define UI_TOOLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_15;
    QLineEdit *lineEditF_nRow;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_10;
    QLineEdit *lineEditF_offsetCol;
    QLineEdit *lineEditF_W;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEditF_H;
    QLabel *label_7;
    QLineEdit *lineEditF_offsetRow;
    QLineEdit *lineEditF_Y;
    QLineEdit *lineEditF_X;
    QLabel *label_9;
    QLineEdit *lineEditF_nCol;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_14;
    QLabel *label_2;
    QWidget *widget;
    QWidget *tab_2;
    QRadioButton *radioButton_createFrame1;
    QRadioButton *radioButton_createFrame2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(570, 337);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Table.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        Dialog->setModal(true);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 551, 281));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 201, 231));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(150, 130, 21, 16));
        lineEditF_nRow = new QLineEdit(groupBox);
        lineEditF_nRow->setObjectName(QString::fromUtf8("lineEditF_nRow"));
        lineEditF_nRow->setGeometry(QRect(90, 110, 41, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 10, 21, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 61, 16));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(110, 90, 21, 16));
        lineEditF_offsetCol = new QLineEdit(groupBox);
        lineEditF_offsetCol->setObjectName(QString::fromUtf8("lineEditF_offsetCol"));
        lineEditF_offsetCol->setGeometry(QRect(140, 150, 41, 20));
        lineEditF_W = new QLineEdit(groupBox);
        lineEditF_W->setObjectName(QString::fromUtf8("lineEditF_W"));
        lineEditF_W->setGeometry(QRect(90, 70, 41, 20));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(150, 90, 21, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 150, 81, 20));
        lineEditF_H = new QLineEdit(groupBox);
        lineEditF_H->setObjectName(QString::fromUtf8("lineEditF_H"));
        lineEditF_H->setGeometry(QRect(140, 70, 41, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(110, 50, 21, 16));
        lineEditF_offsetRow = new QLineEdit(groupBox);
        lineEditF_offsetRow->setObjectName(QString::fromUtf8("lineEditF_offsetRow"));
        lineEditF_offsetRow->setGeometry(QRect(90, 150, 41, 20));
        lineEditF_Y = new QLineEdit(groupBox);
        lineEditF_Y->setObjectName(QString::fromUtf8("lineEditF_Y"));
        lineEditF_Y->setGeometry(QRect(140, 30, 41, 20));
        lineEditF_X = new QLineEdit(groupBox);
        lineEditF_X->setObjectName(QString::fromUtf8("lineEditF_X"));
        lineEditF_X->setGeometry(QRect(90, 30, 41, 20));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(150, 50, 21, 16));
        lineEditF_nCol = new QLineEdit(groupBox);
        lineEditF_nCol->setObjectName(QString::fromUtf8("lineEditF_nCol"));
        lineEditF_nCol->setGeometry(QRect(140, 110, 41, 20));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 110, 61, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 61, 16));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(110, 130, 21, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 10, 21, 16));
        widget = new QWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(220, 20, 321, 221));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/images/createModuleInfo.PNG);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        radioButton_createFrame1 = new QRadioButton(tab_2);
        radioButton_createFrame1->setObjectName(QString::fromUtf8("radioButton_createFrame1"));
        radioButton_createFrame1->setGeometry(QRect(40, 40, 181, 18));
        radioButton_createFrame2 = new QRadioButton(tab_2);
        radioButton_createFrame2->setObjectName(QString::fromUtf8("radioButton_createFrame2"));
        radioButton_createFrame2->setGeometry(QRect(40, 70, 221, 18));
        tabWidget->addTab(tab_2, QString());
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 300, 75, 31));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(430, 300, 75, 31));

        retranslateUi(Dialog);
        QObject::connect(pushButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), Dialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Xedithor : create modules", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "Generate module Sheet", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Dialog", "Col", 0, QApplication::UnicodeUTF8));
        lineEditF_nRow->setText(QApplication::translate("Dialog", "2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Y", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Start Point", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "Row", 0, QApplication::UnicodeUTF8));
        lineEditF_offsetCol->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEditF_W->setText(QApplication::translate("Dialog", "32", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Dialog", "Col", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Dialog", "Row,Col Offset", 0, QApplication::UnicodeUTF8));
        lineEditF_H->setText(QApplication::translate("Dialog", "32", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Dialog", "W", 0, QApplication::UnicodeUTF8));
        lineEditF_offsetRow->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEditF_Y->setText(QApplication::translate("Dialog", "100", 0, QApplication::UnicodeUTF8));
        lineEditF_X->setText(QApplication::translate("Dialog", "100", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Dialog", "H", 0, QApplication::UnicodeUTF8));
        lineEditF_nCol->setText(QApplication::translate("Dialog", "2", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Dialog", "N-Row,Col", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "Size", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Dialog", "Row", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "X", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "create modules", 0, QApplication::UnicodeUTF8));
        radioButton_createFrame1->setText(QApplication::translate("Dialog", "Create 1 module 1 frame", 0, QApplication::UnicodeUTF8));
        radioButton_createFrame2->setText(QApplication::translate("Dialog", "Create all module 1 frame", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Dialog", "create frames", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Dialog", "ok", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dialog", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLDIALOG_H
