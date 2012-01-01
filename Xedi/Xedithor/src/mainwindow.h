// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtableview.h>
#include <QXmlStreamWriter>

#include "editwindow.h"
#include "globalconstant.h"
#include "moduletablemodel.h"
//#include "ui_toolDialog.h"

#include <iostream>

QT_BEGIN_NAMESPACE
    class QAction;
    class QActionGroup;
    class QLabel;
    class QMenu;
    class QToolButton;
    class QToolBar;
    class QScrollArea;
    class QScrollBar;
    class QTableWidget;
    class QAbstractItemView;
    class QTableView;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newFile();
    void open();
    void openDataSprite();
    bool save();
    bool saveAs();
    void about();
    void print();

    void showToolDialog();
    void showContentHelp();
    void showAbout();

    void Add_Clicked();
    void Clone_Clicked();
    void Del_Clicked();
    void Up_Clicked();
    void Down_Clicked();
    void Top_Clicked();
    void Bottom_Clicked();


private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;

   // QLabel *imageLabel;
    QPixmap pixmapOpened;

    int m_lastRowSelectedFT;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    // file
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* printAct;
    QAction* exitAct;
    // tool
    QAction* toolFrameAct;
    //help
    QAction* helpContentAct;
    QAction* helpAboutAct;
    EditWindow *editWindow;
    //Ui::Dialog toolDialogFrm;
    //QDialog* m_toolDialog;
    QToolBar *windowEditToolBar;

    QToolButton* tNavButton[XD::NUM_TAB][XD::NUM_GROUP][XD::NUM_BUTTON];
    QTableView* m_Atable[XD::NUM_TAB][XD::NUM_TABLE];
    // module
    ModuleTableModel* m_moduleTableModel;
    // frame
    ModuleTableModel* m_frameTableModel;
    ModuleTableModel* m_frameDescTableModel;
    // animation
    ModuleTableModel* m_animTableModel;
    ModuleTableModel* m_animDescTableModel;

    QString m_ImgfileName;
    QString m_SprfileName;
    QTimer* m_timer;

    void CreateActions();
    void CreateMainMenus();
    void CreateToolBar();
    void SetupTables();
    void SetupWidgetAlias();
    void SetupConnectWidgets();

    void tableAddRow(QTableView* table);
    void tableCloneRow(QTableView* table);
    void tableDelRow(QTableView* table);
    void tableUpSel(QTableView* table);
    void tableDownSel(QTableView* table);
    void tableTopSel(QTableView* table);
    void tableBotSel(QTableView* table);

    void saveDataSprite();
    void resetDataTable();
    void parseDataRow(QString strDataRow);
    void parseDataRowFrame(QList<QString>&header,QList<QString>&body);
    void parseDataRowAnim(QList<QString>&header,QList<QString>&body);


public slots:
    void tableRowSelected(const QModelIndex& index);
    void UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB);
    void TableEditCompleted(QString str);

    void TableDoubleClicked(const QModelIndex& index);

    //tab widget
    void PageTabChanged(int indexPage);
    void timerHit();


};

#endif // MAINWINDOW_H
