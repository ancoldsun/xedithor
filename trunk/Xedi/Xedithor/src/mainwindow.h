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
#include "mfatablemodel.h"
#include "ui_spriteselector.h"



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
    void openDataSprite(QString path);
    bool save();
    bool saveAs();
    void about();
    void exportSprite();

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

    int silentExportSprite(int i);


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
    MFATableModel* m_MFATableModel;
    // frame
    MFATableModel* m_frameTableModel;
    MFATableModel* m_frameDescTableModel;
    // animation
    MFATableModel* m_animTableModel;
    MFATableModel* m_animDescTableModel;

    QString m_ImgfileName;
    QString m_SprfileName;
    QString m_workingDir;
    QString m_workingExportOutDir;
    QTimer* m_timer;
    Ui::Frame frameUI;

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

    void setupSpriteManager();

    QString removeFileExtension(QString fileName);




public slots:
    void tableRowSelected(const QModelIndex& index);
    void UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB);
    void TableEditCompleted(QString str);

    void TableDoubleClicked(const QModelIndex& index);

    //tab widget
    void PageTabChanged(int indexPage);
    void timerHit();
    void reOffsetFrames();

    void openSpriteFromIndex(int index);
    void spriteListRefresh();
    void exportAll();
    void setWorkDir();

    //table shorcut handle
    void shorcutSetup();
    void cloneModuleShorcut();
    // module
    void arrowDownModuleShorcut();
    void arrowUpModuleShorcut();
    // frame
    void arrowDownFrameShorcut();
    void arrowUpFrameShorcut();
    // frame desc
    void arrowDownFrameDescShorcut();
    void arrowUpFrameDescShorcut();
    // anim
    void arrowDownAnimShorcut();
    void arrowUpAnimShorcut();
    // anim desc
    void arrowDownAnimDescShorcut();
    void arrowUpAnimDescShorcut();

    void moduleTableRowSelected(int selected);
    void frameTableRowSelected(int selected);
    void frameDescTableRowSelected(int selected);
    void animTableRowSelected(int selected);
    void animDescTableRowSelected(int selected);



};

#endif // MAINWINDOW_H
