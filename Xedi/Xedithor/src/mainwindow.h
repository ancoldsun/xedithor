/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtableview.h>

#include "editwindow.h"
#include "globalconstant.h"
#include "moduletablemodel.h"

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
    bool save();
    bool saveAs();
    void about();
    void print();

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
    QMenu *formatMenu;
    QMenu *helpMenu;

   // QLabel *imageLabel;
    QPixmap pixmapOpened;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* printAct;
    QAction* exitAct;

    EditWindow *editWindow;
    QToolBar *windowEditToolBar;

    QToolButton* tNavButton[XD::NUM_TAB][XD::NUM_GROUP][XD::NUM_BUTTON];
    QTableView* m_Atable[XD::NUM_TAB][XD::NUM_TABLE];

    ModuleTableModel* m_moduleTableModel;
    ModuleTableModel* m_frameTableModel;
    ModuleTableModel* m_frameDescTableModel;

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

public slots:
    void tableRowSelected(const QModelIndex& index);
    void UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB);
    void TableEditCompleted(QString str);

    //tab widget
    void PageTabChanged(int indexPage);


};

#endif // MAINWINDOW_H
