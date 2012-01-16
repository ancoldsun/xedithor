/********************************************************************************
** Form generated from reading UI file 'exportdialog.ui'
**
** Created: Sat Jan 14 19:42:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTDIALOG_H
#define UI_EXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *comboBoxFormat;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditTexturePath;
    QToolButton *toolButtonTexturePath;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEditExportOut;
    QToolButton *toolButtonExportOut;

    void setupUi(QDialog *ExportDialog)
    {
        if (ExportDialog->objectName().isEmpty())
            ExportDialog->setObjectName(QString::fromUtf8("ExportDialog"));
        ExportDialog->resize(440, 170);
        buttonBox = new QDialogButtonBox(ExportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setGeometry(QRect(100, 120, 331, 61));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(ExportDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 3, 421, 121));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(40);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(11, 0));

        horizontalLayout_4->addWidget(label_5);

        comboBoxFormat = new QComboBox(horizontalLayoutWidget);
        comboBoxFormat->setObjectName(QString::fromUtf8("comboBoxFormat"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxFormat->sizePolicy().hasHeightForWidth());
        comboBoxFormat->setSizePolicy(sizePolicy1);
        comboBoxFormat->setFrame(true);

        horizontalLayout_4->addWidget(comboBoxFormat);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label_3);

        lineEditTexturePath = new QLineEdit(horizontalLayoutWidget);
        lineEditTexturePath->setObjectName(QString::fromUtf8("lineEditTexturePath"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditTexturePath->sizePolicy().hasHeightForWidth());
        lineEditTexturePath->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(lineEditTexturePath);

        toolButtonTexturePath = new QToolButton(horizontalLayoutWidget);
        toolButtonTexturePath->setObjectName(QString::fromUtf8("toolButtonTexturePath"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(toolButtonTexturePath->sizePolicy().hasHeightForWidth());
        toolButtonTexturePath->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(toolButtonTexturePath);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(40);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);

        horizontalLayout_2->addWidget(label_4);

        lineEditExportOut = new QLineEdit(horizontalLayoutWidget);
        lineEditExportOut->setObjectName(QString::fromUtf8("lineEditExportOut"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(30);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(lineEditExportOut->sizePolicy().hasHeightForWidth());
        lineEditExportOut->setSizePolicy(sizePolicy6);

        horizontalLayout_2->addWidget(lineEditExportOut);

        toolButtonExportOut = new QToolButton(horizontalLayoutWidget);
        toolButtonExportOut->setObjectName(QString::fromUtf8("toolButtonExportOut"));
        sizePolicy4.setHeightForWidth(toolButtonExportOut->sizePolicy().hasHeightForWidth());
        toolButtonExportOut->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(toolButtonExportOut);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(ExportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportDialog)
    {
        ExportDialog->setWindowTitle(QApplication::translate("ExportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ExportDialog", "Format", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ExportDialog", "Texture Packer", 0, QApplication::UnicodeUTF8));
        toolButtonTexturePath->setText(QApplication::translate("ExportDialog", "...", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ExportDialog", "Export Out", 0, QApplication::UnicodeUTF8));
        toolButtonExportOut->setText(QApplication::translate("ExportDialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportDialog: public Ui_ExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTDIALOG_H
