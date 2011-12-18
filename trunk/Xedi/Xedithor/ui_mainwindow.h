/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Dec 17 12:23:30 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockTab;
    QWidget *dockWidgetContents_3;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget;
    QWidget *ImageModuleTab;
    QVBoxLayout *verticalLayout;
    QGroupBox *mt_groupBox1;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *mt_navTable1_button1;
    QToolButton *mt_navTable1_button2;
    QToolButton *mt_navTable1_button3;
    QToolButton *mt_navTable1_button4;
    QToolButton *mt_navTable1_button5;
    QToolButton *mt_navTable1_button6;
    QToolButton *mt_navTable1_button7;
    QTableView *mt_tableView1;
    QGroupBox *groupBox;
    QToolButton *openImageButton;
    QLabel *imagePathInfo;
    QWidget *FrameTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *ft_groupBox1;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *ft_navTable1_button1;
    QToolButton *ft_navTable1_button2;
    QToolButton *ft_navTable1_button3;
    QToolButton *ft_navTable1_button4;
    QToolButton *ft_navTable1_button5;
    QToolButton *ft_navTable1_button6;
    QToolButton *ft_navTable1_button7;
    QTableView *ft_tableView1;
    QDockWidget *dockWidget_ft;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *ft_groupBox2;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *ft_navTable2_button1;
    QToolButton *ft_navTable2_button2;
    QToolButton *ft_navTable2_button3;
    QToolButton *ft_navTable2_button4;
    QToolButton *ft_navTable2_button5;
    QToolButton *ft_navTable2_button6;
    QToolButton *ft_navTable2_button7;
    QTableView *ft_tableView2;
    QWidget *AnimTab;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *at_groupBox1;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *at_navTable1_button1;
    QToolButton *at_navTable1_button2;
    QToolButton *at_navTable1_button3;
    QToolButton *at_navTable1_button4;
    QToolButton *at_navTable1_button5;
    QToolButton *at_navTable1_button6;
    QToolButton *at_navTable1_button7;
    QTableView *at_tableView1;
    QDockWidget *dockWidget_at;
    QWidget *dockWidgetContents_7;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *at_groupBox2;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *at_navTable2_button1;
    QToolButton *at_navTable2_button2;
    QToolButton *at_navTable2_button3;
    QToolButton *at_navTable2_button4;
    QToolButton *at_navTable2_button5;
    QToolButton *at_navTable2_button6;
    QToolButton *at_navTable2_button7;
    QTableView *at_tableView2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(768, 556);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMaximumSize(QSize(20, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 16, 484));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 768, 18));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockTab = new QDockWidget(MainWindow);
        dockTab->setObjectName(QString::fromUtf8("dockTab"));
        dockTab->setStyleSheet(QString::fromUtf8(""));
        dockTab->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        horizontalLayout_5 = new QHBoxLayout(dockWidgetContents_3);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        tabWidget = new QTabWidget(dockWidgetContents_3);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        ImageModuleTab = new QWidget();
        ImageModuleTab->setObjectName(QString::fromUtf8("ImageModuleTab"));
        ImageModuleTab->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(ImageModuleTab);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mt_groupBox1 = new QGroupBox(ImageModuleTab);
        mt_groupBox1->setObjectName(QString::fromUtf8("mt_groupBox1"));
        mt_groupBox1->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        horizontalLayout_3 = new QHBoxLayout(mt_groupBox1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        mt_navTable1_button1 = new QToolButton(mt_groupBox1);
        mt_navTable1_button1->setObjectName(QString::fromUtf8("mt_navTable1_button1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mt_navTable1_button1->sizePolicy().hasHeightForWidth());
        mt_navTable1_button1->setSizePolicy(sizePolicy);
        mt_navTable1_button1->setMinimumSize(QSize(2, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/zoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button1->setIcon(icon);

        horizontalLayout_3->addWidget(mt_navTable1_button1);

        mt_navTable1_button2 = new QToolButton(mt_groupBox1);
        mt_navTable1_button2->setObjectName(QString::fromUtf8("mt_navTable1_button2"));
        sizePolicy.setHeightForWidth(mt_navTable1_button2->sizePolicy().hasHeightForWidth());
        mt_navTable1_button2->setSizePolicy(sizePolicy);
        mt_navTable1_button2->setMinimumSize(QSize(2, 0));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/editRect.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button2->setIcon(icon1);

        horizontalLayout_3->addWidget(mt_navTable1_button2);

        mt_navTable1_button3 = new QToolButton(mt_groupBox1);
        mt_navTable1_button3->setObjectName(QString::fromUtf8("mt_navTable1_button3"));
        sizePolicy.setHeightForWidth(mt_navTable1_button3->sizePolicy().hasHeightForWidth());
        mt_navTable1_button3->setSizePolicy(sizePolicy);
        mt_navTable1_button3->setMinimumSize(QSize(2, 0));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Del.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button3->setIcon(icon2);

        horizontalLayout_3->addWidget(mt_navTable1_button3);

        mt_navTable1_button4 = new QToolButton(mt_groupBox1);
        mt_navTable1_button4->setObjectName(QString::fromUtf8("mt_navTable1_button4"));
        sizePolicy.setHeightForWidth(mt_navTable1_button4->sizePolicy().hasHeightForWidth());
        mt_navTable1_button4->setSizePolicy(sizePolicy);
        mt_navTable1_button4->setMinimumSize(QSize(2, 0));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Up.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button4->setIcon(icon3);

        horizontalLayout_3->addWidget(mt_navTable1_button4);

        mt_navTable1_button5 = new QToolButton(mt_groupBox1);
        mt_navTable1_button5->setObjectName(QString::fromUtf8("mt_navTable1_button5"));
        sizePolicy.setHeightForWidth(mt_navTable1_button5->sizePolicy().hasHeightForWidth());
        mt_navTable1_button5->setSizePolicy(sizePolicy);
        mt_navTable1_button5->setMinimumSize(QSize(2, 0));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Down.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button5->setIcon(icon4);

        horizontalLayout_3->addWidget(mt_navTable1_button5);

        mt_navTable1_button6 = new QToolButton(mt_groupBox1);
        mt_navTable1_button6->setObjectName(QString::fromUtf8("mt_navTable1_button6"));
        sizePolicy.setHeightForWidth(mt_navTable1_button6->sizePolicy().hasHeightForWidth());
        mt_navTable1_button6->setSizePolicy(sizePolicy);
        mt_navTable1_button6->setMinimumSize(QSize(2, 0));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/Top.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button6->setIcon(icon5);

        horizontalLayout_3->addWidget(mt_navTable1_button6);

        mt_navTable1_button7 = new QToolButton(mt_groupBox1);
        mt_navTable1_button7->setObjectName(QString::fromUtf8("mt_navTable1_button7"));
        sizePolicy.setHeightForWidth(mt_navTable1_button7->sizePolicy().hasHeightForWidth());
        mt_navTable1_button7->setSizePolicy(sizePolicy);
        mt_navTable1_button7->setMinimumSize(QSize(2, 0));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/Bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        mt_navTable1_button7->setIcon(icon6);

        horizontalLayout_3->addWidget(mt_navTable1_button7);


        verticalLayout->addWidget(mt_groupBox1);

        mt_tableView1 = new QTableView(ImageModuleTab);
        mt_tableView1->setObjectName(QString::fromUtf8("mt_tableView1"));
        mt_tableView1->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(mt_tableView1);

        groupBox = new QGroupBox(ImageModuleTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        openImageButton = new QToolButton(groupBox);
        openImageButton->setObjectName(QString::fromUtf8("openImageButton"));
        openImageButton->setGeometry(QRect(10, 20, 41, 31));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/Create.png"), QSize(), QIcon::Normal, QIcon::Off);
        openImageButton->setIcon(icon7);
        imagePathInfo = new QLabel(groupBox);
        imagePathInfo->setObjectName(QString::fromUtf8("imagePathInfo"));
        imagePathInfo->setGeometry(QRect(60, 20, 281, 31));
        imagePathInfo->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));

        verticalLayout->addWidget(groupBox);

        tabWidget->addTab(ImageModuleTab, QString());
        FrameTab = new QWidget();
        FrameTab->setObjectName(QString::fromUtf8("FrameTab"));
        verticalLayout_4 = new QVBoxLayout(FrameTab);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ft_groupBox1 = new QGroupBox(FrameTab);
        ft_groupBox1->setObjectName(QString::fromUtf8("ft_groupBox1"));
        ft_groupBox1->setStyleSheet(QString::fromUtf8("background-color: rgb(124, 163, 78);"));
        horizontalLayout_6 = new QHBoxLayout(ft_groupBox1);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        ft_navTable1_button1 = new QToolButton(ft_groupBox1);
        ft_navTable1_button1->setObjectName(QString::fromUtf8("ft_navTable1_button1"));
        sizePolicy.setHeightForWidth(ft_navTable1_button1->sizePolicy().hasHeightForWidth());
        ft_navTable1_button1->setSizePolicy(sizePolicy);
        ft_navTable1_button1->setMinimumSize(QSize(2, 0));
        ft_navTable1_button1->setIcon(icon);

        horizontalLayout_6->addWidget(ft_navTable1_button1);

        ft_navTable1_button2 = new QToolButton(ft_groupBox1);
        ft_navTable1_button2->setObjectName(QString::fromUtf8("ft_navTable1_button2"));
        sizePolicy.setHeightForWidth(ft_navTable1_button2->sizePolicy().hasHeightForWidth());
        ft_navTable1_button2->setSizePolicy(sizePolicy);
        ft_navTable1_button2->setMinimumSize(QSize(2, 0));
        ft_navTable1_button2->setIcon(icon1);

        horizontalLayout_6->addWidget(ft_navTable1_button2);

        ft_navTable1_button3 = new QToolButton(ft_groupBox1);
        ft_navTable1_button3->setObjectName(QString::fromUtf8("ft_navTable1_button3"));
        sizePolicy.setHeightForWidth(ft_navTable1_button3->sizePolicy().hasHeightForWidth());
        ft_navTable1_button3->setSizePolicy(sizePolicy);
        ft_navTable1_button3->setMinimumSize(QSize(2, 0));
        ft_navTable1_button3->setIcon(icon2);

        horizontalLayout_6->addWidget(ft_navTable1_button3);

        ft_navTable1_button4 = new QToolButton(ft_groupBox1);
        ft_navTable1_button4->setObjectName(QString::fromUtf8("ft_navTable1_button4"));
        sizePolicy.setHeightForWidth(ft_navTable1_button4->sizePolicy().hasHeightForWidth());
        ft_navTable1_button4->setSizePolicy(sizePolicy);
        ft_navTable1_button4->setMinimumSize(QSize(2, 0));
        ft_navTable1_button4->setIcon(icon3);

        horizontalLayout_6->addWidget(ft_navTable1_button4);

        ft_navTable1_button5 = new QToolButton(ft_groupBox1);
        ft_navTable1_button5->setObjectName(QString::fromUtf8("ft_navTable1_button5"));
        sizePolicy.setHeightForWidth(ft_navTable1_button5->sizePolicy().hasHeightForWidth());
        ft_navTable1_button5->setSizePolicy(sizePolicy);
        ft_navTable1_button5->setMinimumSize(QSize(2, 0));
        ft_navTable1_button5->setIcon(icon4);

        horizontalLayout_6->addWidget(ft_navTable1_button5);

        ft_navTable1_button6 = new QToolButton(ft_groupBox1);
        ft_navTable1_button6->setObjectName(QString::fromUtf8("ft_navTable1_button6"));
        sizePolicy.setHeightForWidth(ft_navTable1_button6->sizePolicy().hasHeightForWidth());
        ft_navTable1_button6->setSizePolicy(sizePolicy);
        ft_navTable1_button6->setMinimumSize(QSize(2, 0));
        ft_navTable1_button6->setIcon(icon5);

        horizontalLayout_6->addWidget(ft_navTable1_button6);

        ft_navTable1_button7 = new QToolButton(ft_groupBox1);
        ft_navTable1_button7->setObjectName(QString::fromUtf8("ft_navTable1_button7"));
        sizePolicy.setHeightForWidth(ft_navTable1_button7->sizePolicy().hasHeightForWidth());
        ft_navTable1_button7->setSizePolicy(sizePolicy);
        ft_navTable1_button7->setMinimumSize(QSize(2, 0));
        ft_navTable1_button7->setIcon(icon6);

        horizontalLayout_6->addWidget(ft_navTable1_button7);


        verticalLayout_4->addWidget(ft_groupBox1);

        ft_tableView1 = new QTableView(FrameTab);
        ft_tableView1->setObjectName(QString::fromUtf8("ft_tableView1"));

        verticalLayout_4->addWidget(ft_tableView1);

        dockWidget_ft = new QDockWidget(FrameTab);
        dockWidget_ft->setObjectName(QString::fromUtf8("dockWidget_ft"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidget_ft->sizePolicy().hasHeightForWidth());
        dockWidget_ft->setSizePolicy(sizePolicy1);
        dockWidget_ft->setMinimumSize(QSize(350, 199));
        dockWidget_ft->setLayoutDirection(Qt::LeftToRight);
        dockWidget_ft->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        dockWidgetContents_5->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dockWidgetContents_5->sizePolicy().hasHeightForWidth());
        dockWidgetContents_5->setSizePolicy(sizePolicy2);
        dockWidgetContents_5->setLayoutDirection(Qt::LeftToRight);
        dockWidgetContents_5->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        ft_groupBox2 = new QGroupBox(dockWidgetContents_5);
        ft_groupBox2->setObjectName(QString::fromUtf8("ft_groupBox2"));
        horizontalLayout_7 = new QHBoxLayout(ft_groupBox2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        ft_navTable2_button1 = new QToolButton(ft_groupBox2);
        ft_navTable2_button1->setObjectName(QString::fromUtf8("ft_navTable2_button1"));
        sizePolicy.setHeightForWidth(ft_navTable2_button1->sizePolicy().hasHeightForWidth());
        ft_navTable2_button1->setSizePolicy(sizePolicy);
        ft_navTable2_button1->setMinimumSize(QSize(2, 0));
        ft_navTable2_button1->setStyleSheet(QString::fromUtf8(""));
        ft_navTable2_button1->setIcon(icon);

        horizontalLayout_7->addWidget(ft_navTable2_button1);

        ft_navTable2_button2 = new QToolButton(ft_groupBox2);
        ft_navTable2_button2->setObjectName(QString::fromUtf8("ft_navTable2_button2"));
        sizePolicy.setHeightForWidth(ft_navTable2_button2->sizePolicy().hasHeightForWidth());
        ft_navTable2_button2->setSizePolicy(sizePolicy);
        ft_navTable2_button2->setMinimumSize(QSize(2, 0));
        ft_navTable2_button2->setIcon(icon1);

        horizontalLayout_7->addWidget(ft_navTable2_button2);

        ft_navTable2_button3 = new QToolButton(ft_groupBox2);
        ft_navTable2_button3->setObjectName(QString::fromUtf8("ft_navTable2_button3"));
        sizePolicy.setHeightForWidth(ft_navTable2_button3->sizePolicy().hasHeightForWidth());
        ft_navTable2_button3->setSizePolicy(sizePolicy);
        ft_navTable2_button3->setMinimumSize(QSize(2, 0));
        ft_navTable2_button3->setIcon(icon2);

        horizontalLayout_7->addWidget(ft_navTable2_button3);

        ft_navTable2_button4 = new QToolButton(ft_groupBox2);
        ft_navTable2_button4->setObjectName(QString::fromUtf8("ft_navTable2_button4"));
        sizePolicy.setHeightForWidth(ft_navTable2_button4->sizePolicy().hasHeightForWidth());
        ft_navTable2_button4->setSizePolicy(sizePolicy);
        ft_navTable2_button4->setMinimumSize(QSize(2, 0));
        ft_navTable2_button4->setIcon(icon3);

        horizontalLayout_7->addWidget(ft_navTable2_button4);

        ft_navTable2_button5 = new QToolButton(ft_groupBox2);
        ft_navTable2_button5->setObjectName(QString::fromUtf8("ft_navTable2_button5"));
        sizePolicy.setHeightForWidth(ft_navTable2_button5->sizePolicy().hasHeightForWidth());
        ft_navTable2_button5->setSizePolicy(sizePolicy);
        ft_navTable2_button5->setMinimumSize(QSize(2, 0));
        ft_navTable2_button5->setIcon(icon4);

        horizontalLayout_7->addWidget(ft_navTable2_button5);

        ft_navTable2_button6 = new QToolButton(ft_groupBox2);
        ft_navTable2_button6->setObjectName(QString::fromUtf8("ft_navTable2_button6"));
        sizePolicy.setHeightForWidth(ft_navTable2_button6->sizePolicy().hasHeightForWidth());
        ft_navTable2_button6->setSizePolicy(sizePolicy);
        ft_navTable2_button6->setMinimumSize(QSize(2, 0));
        ft_navTable2_button6->setIcon(icon5);

        horizontalLayout_7->addWidget(ft_navTable2_button6);

        ft_navTable2_button7 = new QToolButton(ft_groupBox2);
        ft_navTable2_button7->setObjectName(QString::fromUtf8("ft_navTable2_button7"));
        sizePolicy.setHeightForWidth(ft_navTable2_button7->sizePolicy().hasHeightForWidth());
        ft_navTable2_button7->setSizePolicy(sizePolicy);
        ft_navTable2_button7->setMinimumSize(QSize(2, 0));
        ft_navTable2_button7->setIcon(icon6);

        horizontalLayout_7->addWidget(ft_navTable2_button7);


        verticalLayout_6->addWidget(ft_groupBox2);

        ft_tableView2 = new QTableView(dockWidgetContents_5);
        ft_tableView2->setObjectName(QString::fromUtf8("ft_tableView2"));

        verticalLayout_6->addWidget(ft_tableView2);

        dockWidget_ft->setWidget(dockWidgetContents_5);

        verticalLayout_4->addWidget(dockWidget_ft);

        tabWidget->addTab(FrameTab, QString());
        AnimTab = new QWidget();
        AnimTab->setObjectName(QString::fromUtf8("AnimTab"));
        verticalLayout_8 = new QVBoxLayout(AnimTab);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setContentsMargins(2, 2, 2, 2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        at_groupBox1 = new QGroupBox(AnimTab);
        at_groupBox1->setObjectName(QString::fromUtf8("at_groupBox1"));
        at_groupBox1->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 167, 165);"));
        horizontalLayout_8 = new QHBoxLayout(at_groupBox1);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        at_navTable1_button1 = new QToolButton(at_groupBox1);
        at_navTable1_button1->setObjectName(QString::fromUtf8("at_navTable1_button1"));
        sizePolicy.setHeightForWidth(at_navTable1_button1->sizePolicy().hasHeightForWidth());
        at_navTable1_button1->setSizePolicy(sizePolicy);
        at_navTable1_button1->setMinimumSize(QSize(2, 0));
        at_navTable1_button1->setIcon(icon);

        horizontalLayout_8->addWidget(at_navTable1_button1);

        at_navTable1_button2 = new QToolButton(at_groupBox1);
        at_navTable1_button2->setObjectName(QString::fromUtf8("at_navTable1_button2"));
        sizePolicy.setHeightForWidth(at_navTable1_button2->sizePolicy().hasHeightForWidth());
        at_navTable1_button2->setSizePolicy(sizePolicy);
        at_navTable1_button2->setMinimumSize(QSize(2, 0));
        at_navTable1_button2->setIcon(icon1);

        horizontalLayout_8->addWidget(at_navTable1_button2);

        at_navTable1_button3 = new QToolButton(at_groupBox1);
        at_navTable1_button3->setObjectName(QString::fromUtf8("at_navTable1_button3"));
        sizePolicy.setHeightForWidth(at_navTable1_button3->sizePolicy().hasHeightForWidth());
        at_navTable1_button3->setSizePolicy(sizePolicy);
        at_navTable1_button3->setMinimumSize(QSize(2, 0));
        at_navTable1_button3->setIcon(icon2);

        horizontalLayout_8->addWidget(at_navTable1_button3);

        at_navTable1_button4 = new QToolButton(at_groupBox1);
        at_navTable1_button4->setObjectName(QString::fromUtf8("at_navTable1_button4"));
        sizePolicy.setHeightForWidth(at_navTable1_button4->sizePolicy().hasHeightForWidth());
        at_navTable1_button4->setSizePolicy(sizePolicy);
        at_navTable1_button4->setMinimumSize(QSize(2, 0));
        at_navTable1_button4->setIcon(icon3);

        horizontalLayout_8->addWidget(at_navTable1_button4);

        at_navTable1_button5 = new QToolButton(at_groupBox1);
        at_navTable1_button5->setObjectName(QString::fromUtf8("at_navTable1_button5"));
        sizePolicy.setHeightForWidth(at_navTable1_button5->sizePolicy().hasHeightForWidth());
        at_navTable1_button5->setSizePolicy(sizePolicy);
        at_navTable1_button5->setMinimumSize(QSize(2, 0));
        at_navTable1_button5->setIcon(icon4);

        horizontalLayout_8->addWidget(at_navTable1_button5);

        at_navTable1_button6 = new QToolButton(at_groupBox1);
        at_navTable1_button6->setObjectName(QString::fromUtf8("at_navTable1_button6"));
        sizePolicy.setHeightForWidth(at_navTable1_button6->sizePolicy().hasHeightForWidth());
        at_navTable1_button6->setSizePolicy(sizePolicy);
        at_navTable1_button6->setMinimumSize(QSize(2, 0));
        at_navTable1_button6->setIcon(icon5);

        horizontalLayout_8->addWidget(at_navTable1_button6);

        at_navTable1_button7 = new QToolButton(at_groupBox1);
        at_navTable1_button7->setObjectName(QString::fromUtf8("at_navTable1_button7"));
        sizePolicy.setHeightForWidth(at_navTable1_button7->sizePolicy().hasHeightForWidth());
        at_navTable1_button7->setSizePolicy(sizePolicy);
        at_navTable1_button7->setMinimumSize(QSize(2, 0));
        at_navTable1_button7->setIcon(icon6);

        horizontalLayout_8->addWidget(at_navTable1_button7);


        verticalLayout_8->addWidget(at_groupBox1);

        at_tableView1 = new QTableView(AnimTab);
        at_tableView1->setObjectName(QString::fromUtf8("at_tableView1"));

        verticalLayout_8->addWidget(at_tableView1);

        dockWidget_at = new QDockWidget(AnimTab);
        dockWidget_at->setObjectName(QString::fromUtf8("dockWidget_at"));
        sizePolicy1.setHeightForWidth(dockWidget_at->sizePolicy().hasHeightForWidth());
        dockWidget_at->setSizePolicy(sizePolicy1);
        dockWidget_at->setMinimumSize(QSize(350, 199));
        dockWidget_at->setLayoutDirection(Qt::LeftToRight);
        dockWidget_at->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QString::fromUtf8("dockWidgetContents_7"));
        dockWidgetContents_7->setEnabled(true);
        sizePolicy2.setHeightForWidth(dockWidgetContents_7->sizePolicy().hasHeightForWidth());
        dockWidgetContents_7->setSizePolicy(sizePolicy2);
        dockWidgetContents_7->setLayoutDirection(Qt::LeftToRight);
        dockWidgetContents_7->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_7 = new QVBoxLayout(dockWidgetContents_7);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        at_groupBox2 = new QGroupBox(dockWidgetContents_7);
        at_groupBox2->setObjectName(QString::fromUtf8("at_groupBox2"));
        horizontalLayout_9 = new QHBoxLayout(at_groupBox2);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        at_navTable2_button1 = new QToolButton(at_groupBox2);
        at_navTable2_button1->setObjectName(QString::fromUtf8("at_navTable2_button1"));
        sizePolicy.setHeightForWidth(at_navTable2_button1->sizePolicy().hasHeightForWidth());
        at_navTable2_button1->setSizePolicy(sizePolicy);
        at_navTable2_button1->setMinimumSize(QSize(2, 0));
        at_navTable2_button1->setStyleSheet(QString::fromUtf8(""));
        at_navTable2_button1->setIcon(icon);

        horizontalLayout_9->addWidget(at_navTable2_button1);

        at_navTable2_button2 = new QToolButton(at_groupBox2);
        at_navTable2_button2->setObjectName(QString::fromUtf8("at_navTable2_button2"));
        sizePolicy.setHeightForWidth(at_navTable2_button2->sizePolicy().hasHeightForWidth());
        at_navTable2_button2->setSizePolicy(sizePolicy);
        at_navTable2_button2->setMinimumSize(QSize(2, 0));
        at_navTable2_button2->setIcon(icon1);

        horizontalLayout_9->addWidget(at_navTable2_button2);

        at_navTable2_button3 = new QToolButton(at_groupBox2);
        at_navTable2_button3->setObjectName(QString::fromUtf8("at_navTable2_button3"));
        sizePolicy.setHeightForWidth(at_navTable2_button3->sizePolicy().hasHeightForWidth());
        at_navTable2_button3->setSizePolicy(sizePolicy);
        at_navTable2_button3->setMinimumSize(QSize(2, 0));
        at_navTable2_button3->setIcon(icon2);

        horizontalLayout_9->addWidget(at_navTable2_button3);

        at_navTable2_button4 = new QToolButton(at_groupBox2);
        at_navTable2_button4->setObjectName(QString::fromUtf8("at_navTable2_button4"));
        sizePolicy.setHeightForWidth(at_navTable2_button4->sizePolicy().hasHeightForWidth());
        at_navTable2_button4->setSizePolicy(sizePolicy);
        at_navTable2_button4->setMinimumSize(QSize(2, 0));
        at_navTable2_button4->setIcon(icon3);

        horizontalLayout_9->addWidget(at_navTable2_button4);

        at_navTable2_button5 = new QToolButton(at_groupBox2);
        at_navTable2_button5->setObjectName(QString::fromUtf8("at_navTable2_button5"));
        sizePolicy.setHeightForWidth(at_navTable2_button5->sizePolicy().hasHeightForWidth());
        at_navTable2_button5->setSizePolicy(sizePolicy);
        at_navTable2_button5->setMinimumSize(QSize(2, 0));
        at_navTable2_button5->setIcon(icon4);

        horizontalLayout_9->addWidget(at_navTable2_button5);

        at_navTable2_button6 = new QToolButton(at_groupBox2);
        at_navTable2_button6->setObjectName(QString::fromUtf8("at_navTable2_button6"));
        sizePolicy.setHeightForWidth(at_navTable2_button6->sizePolicy().hasHeightForWidth());
        at_navTable2_button6->setSizePolicy(sizePolicy);
        at_navTable2_button6->setMinimumSize(QSize(2, 0));
        at_navTable2_button6->setIcon(icon5);

        horizontalLayout_9->addWidget(at_navTable2_button6);

        at_navTable2_button7 = new QToolButton(at_groupBox2);
        at_navTable2_button7->setObjectName(QString::fromUtf8("at_navTable2_button7"));
        sizePolicy.setHeightForWidth(at_navTable2_button7->sizePolicy().hasHeightForWidth());
        at_navTable2_button7->setSizePolicy(sizePolicy);
        at_navTable2_button7->setMinimumSize(QSize(2, 0));
        at_navTable2_button7->setIcon(icon6);

        horizontalLayout_9->addWidget(at_navTable2_button7);


        verticalLayout_7->addWidget(at_groupBox2);

        at_tableView2 = new QTableView(dockWidgetContents_7);
        at_tableView2->setObjectName(QString::fromUtf8("at_tableView2"));

        verticalLayout_7->addWidget(at_tableView2);

        dockWidget_at->setWidget(dockWidgetContents_7);

        verticalLayout_8->addWidget(dockWidget_at);

        tabWidget->addTab(AnimTab, QString());

        horizontalLayout_5->addWidget(tabWidget);

        dockTab->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockTab);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Xedithor", 0, QApplication::UnicodeUTF8));
        mt_groupBox1->setTitle(QApplication::translate("MainWindow", "Navigation Table", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        mt_navTable1_button7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Image Source", 0, QApplication::UnicodeUTF8));
        openImageButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        imagePathInfo->setText(QApplication::translate("MainWindow", "Image : None", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(ImageModuleTab), QApplication::translate("MainWindow", "Image Modules", 0, QApplication::UnicodeUTF8));
        ft_groupBox1->setTitle(QApplication::translate("MainWindow", "Navigation Table", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable1_button7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        dockWidgetContents_5->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        dockWidgetContents_5->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        ft_groupBox2->setTitle(QApplication::translate("MainWindow", "Navigation Table", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        ft_navTable2_button7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(FrameTab), QApplication::translate("MainWindow", "Frames", 0, QApplication::UnicodeUTF8));
        at_groupBox1->setTitle(QApplication::translate("MainWindow", "Navigation Table", 0, QApplication::UnicodeUTF8));
        at_navTable1_button1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable1_button7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        dockWidgetContents_7->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        dockWidgetContents_7->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        at_groupBox2->setTitle(QApplication::translate("MainWindow", "Navigation Table", 0, QApplication::UnicodeUTF8));
        at_navTable2_button1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        at_navTable2_button7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(AnimTab), QApplication::translate("MainWindow", "Animations", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
