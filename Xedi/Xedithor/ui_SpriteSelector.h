/********************************************************************************
** Form generated from reading UI file 'spriteselector.ui'
**
** Created: Mon Jan 23 03:54:06 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITESELECTOR_H
#define UI_SPRITESELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_Frame
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QToolButton *tbRefresh;
    QToolButton *tbworkDir;
    QToolButton *tbExportAll;

    void setupUi(QFrame *Frame)
    {
        if (Frame->objectName().isEmpty())
            Frame->setObjectName(QString::fromUtf8("Frame"));
        Frame->resize(405, 43);
        Frame->setFrameShape(QFrame::StyledPanel);
        Frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(Frame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(Frame);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(30);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(comboBox);

        tbRefresh = new QToolButton(Frame);
        tbRefresh->setObjectName(QString::fromUtf8("tbRefresh"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbRefresh->sizePolicy().hasHeightForWidth());
        tbRefresh->setSizePolicy(sizePolicy1);
        tbRefresh->setMinimumSize(QSize(25, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbRefresh->setIcon(icon);

        horizontalLayout->addWidget(tbRefresh);

        tbworkDir = new QToolButton(Frame);
        tbworkDir->setObjectName(QString::fromUtf8("tbworkDir"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbworkDir->sizePolicy().hasHeightForWidth());
        tbworkDir->setSizePolicy(sizePolicy2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbworkDir->setIcon(icon1);

        horizontalLayout->addWidget(tbworkDir);

        tbExportAll = new QToolButton(Frame);
        tbExportAll->setObjectName(QString::fromUtf8("tbExportAll"));
        tbExportAll->setMinimumSize(QSize(25, 0));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Load.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbExportAll->setIcon(icon2);

        horizontalLayout->addWidget(tbExportAll);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Frame);

        QMetaObject::connectSlotsByName(Frame);
    } // setupUi

    void retranslateUi(QFrame *Frame)
    {
        Frame->setWindowTitle(QApplication::translate("Frame", "Frame", 0, QApplication::UnicodeUTF8));
        tbRefresh->setText(QApplication::translate("Frame", "...", 0, QApplication::UnicodeUTF8));
        tbworkDir->setText(QApplication::translate("Frame", "...", 0, QApplication::UnicodeUTF8));
        tbExportAll->setText(QApplication::translate("Frame", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Frame: public Ui_Frame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITESELECTOR_H
