
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uidmanager.h"
#include "packtextureparser.h"
#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "setworkdirdialog.h"
#include "ui_toolDialog.h"
#include "appconfig.h"

#include "spriteexporter.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // alias widget
    SetupWidgetAlias();
    // init
    CreateActions();
    CreateMainMenus();
    CreateToolBar();
    // setup table
    editWindow = new EditWindow(0);
    setCentralWidget(editWindow);
    // setup table
    SetupTables();

    //connect signal-slot
    SetupConnectWidgets();

    m_ImgfileName="none";
    m_SprfileName="none";

    m_lastRowSelectedFT = 0;

    ui->tabWidget->setTabEnabled(Page::SEQANIM, false);
    ui->tabWidget->setTabEnabled(Page::ANIM, false);
    ui->tabWidget->setCurrentIndex(Page::MODULE);

    m_workingDir="";
    m_workingExportOutDir="";
    //open app setting files
    m_workingDir          = AppConfig::getInstance()->Config.workingDir;
    m_workingExportOutDir = AppConfig::getInstance()->Config.exportDir;
    m_exportSrcDir        = AppConfig::getInstance()->Config.exportDirSrc;
    m_packageName         = AppConfig::getInstance()->Config.package;

    setupSpriteManager();

    shorcutSetup();

    m_silenExport=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateActions()
{
    newAct = new QAction(QIcon(":/images/new.png"),tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"),tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    // for open sprite def file
    connect(openAct, SIGNAL(triggered()), this, SLOT(openDataSprite()));

    saveAct = new QAction(QIcon(":/images/save.png"),tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    //printAct = new QAction(QIcon(":/images/paste.png"),tr("&Export..."), this);
    //printAct->setShortcuts(QKeySequence::Print);
    //printAct->setStatusTip(tr("Export Sprite"));
    //connect(printAct, SIGNAL(triggered()), this, SLOT(exportSprite()));

    exitAct = new QAction(QIcon(":/images/new.png"),tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // tool
    toolFrameAct = new QAction(QIcon(":/images/Calculator.png"),tr("&Create"), this);
    //toolFrameAct->setShortcuts(QKeySequence::Save);
    //toolFrameAct->setStatusTip(tr("Save the document to disk"));
    connect(toolFrameAct, SIGNAL(triggered()), this, SLOT(showToolDialog()));

    //help
    helpContentAct = new QAction(tr("&Contents"), this);
    //helpContentAct->setShortcuts(QKeySequence::Save);
    //helpContentAct->setStatusTip(tr("Save the document to disk"));
    //connect(helpContentAct, SIGNAL(triggered()), this, SLOT(showContentHelp()));

    helpAboutAct = new QAction(tr("&About"), this);
    helpAboutAct->setShortcuts(QKeySequence::HelpContents);
    helpAboutAct->setStatusTip(tr("Open About"));
    connect(helpAboutAct, SIGNAL(triggered()), this, SLOT(showAbout()));

    // open image button
    connect(ui->openImageButton, SIGNAL(clicked()), this, SLOT(open()));

}

void MainWindow::CreateMainMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File  "));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    //fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    //edit
    editMenu = menuBar()->addMenu(tr("&Edit  "));
    //tool
    toolMenu = menuBar()->addMenu(tr("&Tool  "));
    toolMenu->addAction(toolFrameAct);
    //help
    helpMenu = menuBar()->addMenu(tr("&Help  "));
    helpMenu->addAction(helpContentAct);
    helpMenu->addAction(helpAboutAct);
}

void MainWindow::CreateToolBar()
{
    ui->mainToolBar->addAction(newAct);
    ui->mainToolBar->addAction(openAct);
    ui->mainToolBar->addAction(saveAct);
    //ui->mainToolBar->addAction(printAct);
}

void MainWindow::SetupTables()
{
    /* module */
    m_MFATableModel = new MFATableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new ModuleRowDataHandler());
    m_MFATableModel->AddEditableColumn(2);
    m_MFATableModel->AddEditableColumn(3);
    m_MFATableModel->AddEditableColumn(4);
    m_MFATableModel->AddEditableColumn(5);
    ui->mt_tableView1->setModel(m_MFATableModel);
    ui->mt_tableView1->setSelectionBehavior(QTableView::SelectRows);

    int width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->mt_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->mt_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->mt_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));
    connect(ui->mt_tableView1->model(),SIGNAL(editCompleted(QString)),this,SLOT(TableEditCompleted(QString)));
    connect(ui->mt_tableView1,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(TableDoubleClicked(QModelIndex)));

    editWindow->imageLabel->m_table = ui->mt_tableView1;

    /*frame - top table */
    m_frameTableModel = new MFATableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new FrameRowDataHandler());
    m_frameTableModel->setHasModel(true);
    m_frameTableModel->setSubModelRowHandler(new FrameDescRowDataHandler());
    ui->ft_tableView1->setModel(m_frameTableModel);
    ui->ft_tableView1->setSelectionBehavior(QTableView::SelectRows);
    m_frameTableModel->AddEditableColumn(3);

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->ft_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->ft_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->ft_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));

    /*frame - bottom table*/
    m_frameDescTableModel = new MFATableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new FrameDescRowDataHandler());
    ui->ft_tableView2->setModel(m_frameDescTableModel);
    ui->ft_tableView2->setSelectionBehavior(QTableView::SelectRows);

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->ft_tableView2->setColumnWidth(m, width_col);
    }
    connect(ui->ft_tableView2, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->ft_tableView2->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));
    //connect(ui->ft_tableView2->model(),SIGNAL(editCompleted(QString)),this,SLOT(TableEditCompleted(QString)));

    // anim top
    m_animTableModel = new MFATableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new AnimRowDataHandler());
    m_animTableModel->setHasModel(true);
    m_animTableModel->setSubModelRowHandler(new AnimDescRowDataHandler());
    ui->at_tableView1->setModel(m_animTableModel);
    ui->at_tableView1->setSelectionBehavior(QTableView::SelectRows);
    m_animTableModel->AddEditableColumn(3); // anim name column

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->at_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->at_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->at_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));

    //frame anim
    m_animDescTableModel = new MFATableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new AnimDescRowDataHandler());
    ui->at_tableView2->setModel(m_animDescTableModel);
    ui->at_tableView2->setSelectionBehavior(QTableView::SelectRows);
    m_animDescTableModel->AddEditableColumn(4); // timeline column

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->at_tableView2->setColumnWidth(m, width_col);
    }
    connect(ui->at_tableView2, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
}

void MainWindow::SetupWidgetAlias()
{
    //button
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
    tNavButton[XD::T_MODULE][XD::GROUP1][XD::B_ADD] = ui->ft_navTable1_button1;
}

void MainWindow::SetupConnectWidgets()
{
   // Tab Module
     // table 1
     connect(ui->mt_navTable1_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->mt_navTable1_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->mt_navTable1_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->mt_navTable1_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->mt_navTable1_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->mt_navTable1_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->mt_navTable1_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
   // Tab Frame
     // table 1
     connect(ui->ft_navTable1_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->ft_navTable1_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->ft_navTable1_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->ft_navTable1_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->ft_navTable1_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->ft_navTable1_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->ft_navTable1_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
     // table 2
     connect(ui->ft_navTable2_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->ft_navTable2_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->ft_navTable2_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->ft_navTable2_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->ft_navTable2_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->ft_navTable2_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->ft_navTable2_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
     connect(ui->ft_navTable2_button8, SIGNAL(clicked()), this, SLOT(reOffsetFrames()));
   // Tab Anim
     // table 1
     connect(ui->at_navTable1_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->at_navTable1_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->at_navTable1_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->at_navTable1_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->at_navTable1_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->at_navTable1_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->at_navTable1_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
     // table 2
     connect(ui->at_navTable2_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->at_navTable2_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->at_navTable2_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->at_navTable2_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->at_navTable2_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->at_navTable2_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->at_navTable2_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));

     //tab widget connect
     connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(PageTabChanged(int)));

     //timer
     m_timer = new QTimer(this);
     m_timer->setInterval(200);
     connect(m_timer, SIGNAL(timeout()), this, SLOT(timerHit()));
}

void MainWindow::newFile()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:
          saveDataSprite();
          break;
      case QMessageBox::Discard:
          // Don't Save was clicked
          break;
      case QMessageBox::Cancel:
          return;
    }
    this->resetDataTable();
    editWindow->getModuleList()->clear();
    editWindow->imageLabel->clearGraphPixmapItem();

    UID::Instance().resetUID();
    m_SprfileName="";
    m_ImgfileName="Image : None";
    ui->imagePathInfo->setText(m_ImgfileName);
}

void MainWindow::open()
{
    m_ImgfileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
    if (!m_ImgfileName.isEmpty()) {
        QImage image(m_ImgfileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Xedithor"),
                                     tr("Cannot load %1.").arg(m_ImgfileName));
            return;
        }

        pixmapOpened =QPixmap::fromImage(image);
        editWindow->imageLabel->setImageGraphicsItem(&pixmapOpened);
        editWindow->scaleFactor = 1.0;
        //printAct->setEnabled(true);
        //update info path image
        ui->imagePathInfo->setText(m_ImgfileName);
    }
}

bool MainWindow::save()
{
    saveDataSprite();
    return true;
}

bool MainWindow::saveAs()
{
    return true;
}

void MainWindow::about()
{

}

void MainWindow::exportSprite()
{
    ExportDialog* expDlg = new ExportDialog(this);
    int retValue = expDlg->exec();

    if(retValue == QDialog::Accepted)
    {
        reOffsetFrames();
        QString exportOutBin      = expDlg->getTexturePackerOut();
        QString texturePackerPath = expDlg->getTexturePacker();
        int formatExport = expDlg->getExportFormat();

        MFATableModel* _moduleModel = static_cast<MFATableModel*>(ui->mt_tableView1->model());
        MFATableModel* _frameModel  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
        MFATableModel* _animModel   = static_cast<MFATableModel*>(ui->at_tableView1->model());

        SpriteExporter exporter(this->pixmapOpened,
                                _moduleModel,
                                _frameModel,
                                _animModel,
                                formatExport);
        exporter.setTexturePackerPath(texturePackerPath);
        exporter.setExportOutPath(exportOutBin);
        exporter.setImgSrcPath(this->m_ImgfileName);
        exporter.setExportOutSrcPath(m_exportSrcDir);
        exporter.setPackageName(m_packageName);

        QFileInfo fi(this->m_SprfileName);
        QString name = fi.baseName();
        exporter.setSprName(name);
        int checkExport = exporter.DoExporting();

        if(checkExport!=0){
            //error
            QMessageBox::critical(this,
                               "Xedithor: export sprite",
                               "Error when exporting, Error Code "+QString::number(checkExport),
                               QMessageBox::Ok);
        }

    }

    delete expDlg;
    expDlg=NULL;
}

void MainWindow::showToolDialog()
{
   QDialog* dialogTool = new QDialog(this);
   Ui::Dialog toolDialogFrm;
   toolDialogFrm.setupUi(dialogTool);

   int retValue = dialogTool->exec();

   if(retValue == QDialog::Accepted)
   {
       if(toolDialogFrm.tabWidget->currentIndex()==0){
            int _startX    = toolDialogFrm.lineEditF_X->text().toInt();
            int _startY    = toolDialogFrm.lineEditF_Y->text().toInt();
            int _modW      = toolDialogFrm.lineEditF_W->text().toInt();
            int _modH      = toolDialogFrm.lineEditF_H->text().toInt();
            int _createnRow= toolDialogFrm.lineEditF_nRow->text().toInt();
            int _createnCol= toolDialogFrm.lineEditF_nCol->text().toInt();
            int _offsetRow = toolDialogFrm.lineEditF_offsetRow->text().toInt();
            int _offsetCol = toolDialogFrm.lineEditF_offsetCol->text().toInt();

            MFATableModel* _model = static_cast<MFATableModel*>(ui->mt_tableView1->model());

            for(int i=0;i<_createnRow;i++){
                for(int j=0;j<_createnCol;j++)
                {
                    int xModValue=_startX + _modW*j + _offsetCol*j;
                    int yModValue=_startY + _modH*i + _offsetRow*i;

                    ui->mt_tableView1->model()->insertRow(_model->rowCount());
                    RowData* _rowData = _model->getDatainRow(_model->rowCount()-1);

                    _rowData->setData(2,QString::number(xModValue));
                    _rowData->setData(3,QString::number(yModValue));
                    _rowData->setData(4,QString::number(_modW));
                    _rowData->setData(5,QString::number(_modH));
                }
            }
           _model->refresh();
       }
       else if(toolDialogFrm.tabWidget->currentIndex()==1){
            ui->tabWidget->setCurrentIndex(Page::FRAME);
            // todo : implemented this
            //QMessageBox msg;
            //msg.setText("not implemented yet");
            //msg.exec();
            MFATableModel* _modelModule = static_cast<MFATableModel*>(ui->mt_tableView1->model());
            MFATableModel* _modelFrame  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
            int moduleCount = _modelModule->rowCount();
            for(int i=0;i<moduleCount;i++){
                tableAddRow(ui->ft_tableView1);

                MFATableModel* _sub_model = _modelFrame->getModel(i);
                _sub_model->insertRow(0);
                /* set data */
                RowData* _row_data        = _sub_model->getDatainRow(0);
                RowData* _row_data_module = _modelModule->getDatainRow(i);

                QString moduleIDStr = _row_data_module->getData(1);
                _row_data->setData(0,QString::number(i));
                _row_data->setData(1,moduleIDStr);

                _modelFrame->getDatainRow(i)->setData(2,"1");
            }
       }
   }
   delete dialogTool;
   dialogTool=NULL;
}

void MainWindow::showContentHelp()
{
    //int returnModal = m_toolDialog->exec();
   // std::cout<<"returnModal.."<<returnModal<<std::endl;
}

void MainWindow::showAbout()
{
    QString strAb = "Xedithor 1.0.0 : 2D Sprite Editor";
    strAb = strAb + "\n";
    strAb = strAb + "\nBased on Qt 4.7.4 (32 bit)";
    strAb = strAb + "\n";
    strAb = strAb + "\nBuilt on 31 12 2011 at 00:14:13";
    strAb = strAb + "\n";
    strAb = strAb + "\nCopyright 2011-2012  Edi Ermawan <edi.ermawan@gmail.com>";
    strAb = strAb + "\n";
    strAb = strAb + "\nStill under development, help is welcomed !";
    strAb = strAb + "\nVisit: http://offground.wordpress.com/";
    QMessageBox::about(this,"About Xedithor",strAb);

}

//table button clicked
void MainWindow::Add_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();

    if(sender == ui->mt_navTable1_button1 ){
        tableAddRow(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button1){
        tableAddRow(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button1){
       tableAddRow(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button1){
        tableAddRow(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button1){
        tableAddRow(ui->at_tableView2);
    }

}

void MainWindow::Clone_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button2 ){
        tableCloneRow(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button2){
        tableCloneRow(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button2){
       tableCloneRow(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button2){
        tableCloneRow(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button2){
        tableCloneRow(ui->at_tableView2);
    }
}

void MainWindow::Del_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button3 ){
        tableDelRow(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button3){
        tableDelRow(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button3){


        int row_ = ui->ft_tableView2->currentIndex().row();
        if(row_ != -1){
            /* del item on graphics view */
            MFATableModel* m = static_cast<MFATableModel*>(ui->ft_tableView2->model());
            RowData* rd = m->getDatainRow(row_);
            int id_ =rd->getData(0).toInt();

            editWindow->imageLabel->DeletePixmapItem(id_);
            /* end del */

            /* update module frame count */
            row_ = ui->ft_tableView1->currentIndex().row();

            if(row_ == -1){
                row_ = 0;
            }
            m = static_cast<MFATableModel*>(ui->ft_tableView1->model());
            int mf_count = m->getDatainRow(row_)->getData(2).toInt();
            m->getDatainRow(row_)->setData(2,QString::number(mf_count-1));
            m->refresh();

            tableDelRow(ui->ft_tableView2);
        }
    }
    else if(sender == ui->at_navTable1_button3){
        tableDelRow(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button3){
        int anim_subtablecurrentrow = ui->at_tableView2->currentIndex().row();
        if(anim_subtablecurrentrow != -1){

            MFATableModel* _model = static_cast<MFATableModel*>(ui->at_tableView2->model());
            anim_subtablecurrentrow = ui->at_tableView1->currentIndex().row();

            if(anim_subtablecurrentrow == -1){
                anim_subtablecurrentrow = 0;
            }
            _model = static_cast<MFATableModel*>(ui->at_tableView1->model());
            int mf_count = _model->getDatainRow(anim_subtablecurrentrow)->getData(2).toInt();
            _model->getDatainRow(anim_subtablecurrentrow)->setData(2,QString::number(mf_count-1));
            _model->refresh();

            tableDelRow(ui->at_tableView2);
        }
    }
}

void MainWindow::Up_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button4 ){
        tableUpSel(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button4){
        tableUpSel(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button4){
       tableUpSel(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button4){
        tableUpSel(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button4){
        tableUpSel(ui->at_tableView2);
    }
}

void MainWindow::Down_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button5 ){
        tableDownSel(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button5){
        tableDownSel(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button5){
       tableDownSel(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button5){
        tableDownSel(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button5){
        tableDownSel(ui->at_tableView2);
    }
}

void MainWindow::Top_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button6 ){
        tableTopSel(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button6){
        tableTopSel(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button6){
       tableTopSel(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button6){
        tableTopSel(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button6){
        tableTopSel(ui->at_tableView2);
    }
}

void MainWindow::Bottom_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button7 ){
        tableBotSel(ui->mt_tableView1);
    }
    else if(sender == ui->ft_navTable1_button7){
        tableBotSel(ui->ft_tableView1);
    }
    else if(sender == ui->ft_navTable2_button7){
       tableBotSel(ui->ft_tableView2);
    }
    else if(sender == ui->at_navTable1_button7){
        tableBotSel(ui->at_tableView1);
    }
    else if(sender == ui->at_navTable2_button7){
        tableBotSel(ui->at_tableView2);
    }
}


void MainWindow::tableAddRow(QTableView* table)
{
   int newRow = table->currentIndex().row();
   if(newRow==-1)
       newRow=0;

   MFATableModel* m = static_cast<MFATableModel*>(table->model());
   table->model()->insertRow(m->rowCount());

   if(newRow==0){
       QModelIndex index = table->model()->index(newRow,0);
       table->setCurrentIndex(index);
   }else {
       QModelIndex index = table->model()->index(newRow+1,0);
       table->setCurrentIndex(index);
   }

   m->refresh();
}

void MainWindow::tableCloneRow(QTableView* table)
{
    int rowToClone = table->currentIndex().row();
    if(rowToClone !=-1)
    {
        MFATableModel* m = static_cast<MFATableModel*>(table->model());
        m->cloneRow(rowToClone);
        QModelIndex index = table->model()->index(rowToClone+1,0);
        table->setCurrentIndex(index);
    }
}

void MainWindow::tableDelRow(QTableView* table)
{
    MFATableModel* m = static_cast<MFATableModel*>(table->model());
    int currRow = table->currentIndex().row();
    if(m->rowCount()>0 && currRow !=-1)
    {
        m->removeRows(currRow,1);
    }
}

void MainWindow::tableUpSel(QTableView* table)
{
    int currRow = table->currentIndex().row();
    if(currRow>0)
    {
        MFATableModel* m = static_cast<MFATableModel*>(table->model());
        m->swapRow(currRow,--currRow);
        table->setCurrentIndex(table->model()->index(currRow , 0, QModelIndex()));
    }
}

void MainWindow::tableDownSel(QTableView* table)
{
    int currRow = table->currentIndex().row();

    MFATableModel* m = static_cast<MFATableModel*>(table->model());
    if(currRow<m->rowCount()-1)
    {
        m->swapRow(currRow,++currRow);
        table->setCurrentIndex(table->model()->index(currRow , 0, QModelIndex()));
    }

}

void MainWindow::tableTopSel(QTableView* table)
{
    table->setCurrentIndex(table->model()->index(0 , 0, QModelIndex()));
    int currRow = table->currentIndex().row();
    MFATableModel* m = static_cast<MFATableModel*>(table->model());

    m->swapRow(currRow,0);
}

void MainWindow::tableBotSel(QTableView* table)
{
    MFATableModel* m = static_cast<MFATableModel*>(table->model());
    int currRow = table->currentIndex().row();
    table->setCurrentIndex(table->model()->index(m->rowCount()-1 , 0, QModelIndex()));

    m->swapRow(currRow,m->rowCount()-1);
}

void MainWindow::tableRowSelected(const QModelIndex& index)
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_tableView1 ){   // table module

        int rowSelected_ = ui->mt_tableView1->currentIndex().row();
        moduleTableRowSelected(rowSelected_);
    }
    else if(sender == ui->ft_tableView1){   // table frame 1
        int rowSelected_ = ui->ft_tableView1->currentIndex().row();
        frameTableRowSelected(rowSelected_);

    } else if(sender == ui->ft_tableView2){ // table module-frame

        int rowSelected_ = ui->ft_tableView2->currentIndex().row();
        frameDescTableRowSelected(rowSelected_);

    }  else if(sender == ui->at_tableView1){ // table anim

        if(editWindow->modulesList->count()>0)
        {
            int _rowSelected = ui->at_tableView1->currentIndex().row();
            animTableRowSelected(_rowSelected);
        }
    } else if(sender == ui->at_tableView2) {     // // table frame anim
        animDescTableRowSelected(-1);
      }
}

void MainWindow::moduleTableRowSelected(int selected)
{
    MFATableModel* m = static_cast<MFATableModel*>(ui->mt_tableView1->model());
    RowData* rd = m->getDatainRow(selected);

    qreal px_ =rd->getData(2).toInt();//.toDouble();
    qreal py_ =rd->getData(3).toInt();//.toDouble();
    qreal w_  =rd->getData(4).toInt();//.toDouble();
    qreal h_  =rd->getData(5).toInt();//.toDouble();

    /* slice image */
    QPixmap pieceImage =pixmapOpened.copy(px_, py_, w_, h_);
    int idx = editWindow->getModuleList()->count();
    if(idx > 1)
    {
        QListWidgetItem *item = editWindow->getModuleList()->takeItem(0);
        delete item;
    }
    editWindow->getModuleList()->clear();
    editWindow->getModuleList()->addPiece(pieceImage,QPoint(0,0));
    /* end slice image */

    QRectF rect_ = editWindow->imageLabel->getRectSelectItem()->rect();
    rect_.setHeight(h_);
    rect_.setWidth(w_);
    editWindow->imageLabel->getRectSelectItem()->setRect(rect_);

    px_=px_-rect_.x()+(WidthRectView/2);
    py_=py_-rect_.y()+(HeightRectView/2);
    editWindow->imageLabel->getRectSelectItem()->setPos(px_,py_);
}

void MainWindow::frameTableRowSelected(int selected)
{
    if(m_lastRowSelectedFT != selected)
    {
        m_lastRowSelectedFT = selected;
        MFATableModel* mf = static_cast<MFATableModel*>(ui->ft_tableView1->model());
        MFATableModel* mf_bottom = mf->getModel(selected);
        ui->ft_tableView2->setModel(mf_bottom);
        // clear prev row images item
        editWindow->imageLabel->clearGraphPixmapItem();
        // create
        for(int i=0;i<mf_bottom->rowCount();i++)
        {
            RowData* rd = mf_bottom->getDatainRow(i);

            int id_           = rd->getData(0).toInt();
            QString moduleID_ = rd->getData(1);
            int px_           = rd->getData(2).toInt();
            int py_           = rd->getData(3).toInt();
            //qreal w_    =rd->getData(4).toDouble();
            //qreal h_    =rd->getData(5).toDouble();

            QListWidgetItem* _item = editWindow->modulesList->getItemByText(moduleID_);
            if(_item!=NULL)
            {
                QPixmap pixmap      = _item->icon().pixmap(ITEM_PIXMAP::Max_W,ITEM_PIXMAP::Max_H);
                QPixmap copyPixmap = pixmap.copy();
                editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);
            }
            else
            {
                QPixmap pixmap = QPixmap::fromImage(QImage(":/images/invalid.png"));
                editWindow->imageLabel->AddPixmapItem(&pixmap,false,id_,px_,py_);
            }
        }
    }
}

void MainWindow::frameDescTableRowSelected(int selected)
{
    MFATableModel* mf = static_cast<MFATableModel*>(ui->ft_tableView2->model());
    RowData* _row_data          = mf->getDatainRow(selected);
    int id_                     = _row_data->getData(0).toInt();
    editWindow->imageLabel->setSelectedPixmapItem(id_);
}

void MainWindow::animTableRowSelected(int selected)
{
    MFATableModel* _anim_model       = static_cast<MFATableModel*>(ui->at_tableView1->model());
    MFATableModel* _frame_anim_model = _anim_model->getModel(selected);
    ui->at_tableView2->setModel(_frame_anim_model);

    // clear prev row images item
    editWindow->imageLabel->clearGraphPixmapItem();
    editWindow->createAnimation();
}

void MainWindow::animDescTableRowSelected(int selected)
{
    editWindow->imageLabel->clearAnimation();

    MFATableModel* frameAnimModel= static_cast<MFATableModel*>(ui->at_tableView2->model());

    // clear prev row images item
    editWindow->imageLabel->clearGraphPixmapItem();

    int i = ui->at_tableView2->currentIndex().row();
    RowData* rd = frameAnimModel->getDatainRow(i);

    int id_           = rd->getData(0).toInt();
    QString moduleID_ = rd->getData(1);
    int px_           = rd->getData(2).toInt();
    int py_           = rd->getData(3).toInt();

    QListWidgetItem* _item = editWindow->modulesList->getItemByText(moduleID_);
    if(_item!=NULL)
    {
        QPixmap pixmap      = _item->icon().pixmap(ITEM_PIXMAP::Max_W,ITEM_PIXMAP::Max_H);
        QPixmap copyPixmap = pixmap.copy();
        editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);
    }
}

void MainWindow::UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB)
{
    // todo:

}

void MainWindow::TableEditCompleted(QString str)
{
    int rowSelected_ = ui->mt_tableView1->currentIndex().row();

    MFATableModel* m = static_cast<MFATableModel*>(ui->mt_tableView1->model());
    RowData* rd = m->getDatainRow(rowSelected_);

    qreal px_ =rd->getData(2).toDouble();
    qreal py_ =rd->getData(3).toDouble();
    qreal w_  =rd->getData(4).toDouble();
    qreal h_  =rd->getData(5).toDouble();

    QRectF rect_ = editWindow->imageLabel->getRectSelectItem()->rect();
    rect_.setHeight(h_);
    rect_.setWidth(w_);
    editWindow->imageLabel->getRectSelectItem()->setRect(rect_);

    px_=px_-rect_.x()+(WidthRectView/2);
    py_=py_-rect_.y()+(HeightRectView/2);
    editWindow->imageLabel->getRectSelectItem()->setPos(px_,py_);
}


 void MainWindow::PageTabChanged(int indexPage)
 {
     if(indexPage== Page::MODULE)
     {
        editWindow->getModuleList()->clear();
        // set to modules table
        editWindow->imageLabel->m_table = ui->mt_tableView1;
        editWindow->imageLabel->m_table_bottom=NULL;
        editWindow->setupViewModule();//imageLabel->setupGraphViewModule();

        ui->tabWidget->setTabEnabled(Page::ANIM, false);
     }
     else if(indexPage == Page::FRAME)
     {
         m_lastRowSelectedFT =-1;
         editWindow->getModuleList()->clear();
         MFATableModel* m = static_cast<MFATableModel*>(ui->mt_tableView1->model());

         editWindow->getModuleList()->clear();
         for(int i=0;i<m->rowCount();i++)
         {
             RowData* rd = m->getDatainRow(i);

             QString id_ =rd->getData(1);
             qreal px_   =rd->getData(2).toDouble();
             qreal py_   =rd->getData(3).toDouble();
             qreal w_    =rd->getData(4).toDouble();
             qreal h_    =rd->getData(5).toDouble();

             /* slice image */
             QPixmap pieceImage =pixmapOpened.copy(px_, py_, w_, h_);

             editWindow->getModuleList()->addPiece(pieceImage,QPoint(i,0),id_);
             /* end slice image */
         }
         // graph now handle frame table
         editWindow->imageLabel->m_table = ui->ft_tableView1;
         editWindow->imageLabel->m_table_bottom = ui->ft_tableView2;
         editWindow->setupViewFrame();
         m_timer->start(200);
         ui->tabWidget->setTabEnabled(Page::ANIM, true);

     }
     else if(indexPage == Page::ANIM)
     {
        MFATableModel* m  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
        MFATableModel* m2;

        //std::cout<<" indexPage == Page::ANIM :"<<(editWindow->modulesList->count())<<std::endl;
        if(editWindow->modulesList->count()>0) {

            m_ListPxmap.clear();
            m_ListStrFrameID.clear();
            std::cout<<" m->rowCount():"<<(m->rowCount())<<std::endl;
            editWindow->imageLabel->hideAxis();
            for(int i=0;i<m->rowCount();i++)
            {
                if(m->getDatainRow(i)->getData(2).toInt()>0)
                {
                    editWindow->imageLabel->clearGraphPixmapItem();
                    m2 = m->getModel(i);
                    int nModuleInFrame = 0;
                    for(int j=0;j<m2->rowCount();j++)
                    {
                        RowData* rd       = m2->getDatainRow(j);
                        int id_           = rd->getData(0).toInt();
                        QString moduleID_ = rd->getData(1);
                        int px_           = rd->getData(2).toInt();
                        int py_           = rd->getData(3).toInt();
                        QListWidgetItem* _img_item = editWindow->modulesList->getItemByText(moduleID_);

                        if(_img_item!=NULL)
                        {
                                QIcon _icon = _img_item->icon();
                                QPixmap pixmap = _icon.pixmap(ITEM_PIXMAP::Max_W,ITEM_PIXMAP::Max_H);
                                QPixmap copyPixmap = pixmap.copy();
                                editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);
                                nModuleInFrame++;
                                rd->setValid(true);
                        }
                        else
                        {
                                QPixmap pixmap = QPixmap::fromImage(QImage(":/images/invalidF.png"));
                                editWindow->imageLabel->AddPixmapItem(&pixmap,false,id_,px_,py_);
                                nModuleInFrame++;
                                rd->setValid(false);
                        }
                    }
                    if(nModuleInFrame>0)
                    {
                        QPixmap pieceImage =QPixmap::fromImage((editWindow->imageLabel->exportToImage()));
                        m_ListStrFrameID.push_back(m->getDatainRow(i)->getData(1));
                        m_ListPxmap.push_back(pieceImage);
                    }
                }
            }
            editWindow->imageLabel->showAxis();
            editWindow->getModuleList()->clear();
            editWindow->imageLabel->clearGraphPixmapItem();

            for(int i=0;i<m_ListPxmap.count();i++)
            {
                QPixmap _pixmap = m_ListPxmap.at(i);
                editWindow->getModuleList()->addPiece(_pixmap,QPoint(0,0),m_ListStrFrameID.at(i));
            }
        }
        editWindow->setupViewAnim();
        editWindow->imageLabel->m_table        = ui->at_tableView1;
        editWindow->imageLabel->m_table_bottom = ui->at_tableView2;

    }
 }
 void MainWindow::saveDataSprite() // // todo : separate this to other class
 {
    qDebug(m_SprfileName.toUtf8());
     if(!m_SprfileName.compare("none") || !m_SprfileName.compare(""))
    {
        QString fileFilter="*.xml;;*.xdr";
        m_SprfileName = QFileDialog::getSaveFileName(this,tr("Open File"), QDir::currentPath(),fileFilter);
    }
    QFile output(m_SprfileName);
    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeComment("xedithor's sprite file");
    stream.writeComment("last saved: 18/12/2011 17:34");// todo : replace w/ actual value
    stream.writeStartElement("sprites");
    /* save img path */
    stream.writeStartElement("image");
    stream.writeTextElement("path", m_ImgfileName);
    stream.writeEndElement(); // image
    /* save modules */
    stream.writeStartElement("modules");
    int numberRow = m_MFATableModel->rowCount();
    QString numberRowStr = QString::number(numberRow);
    stream.writeAttribute("nModules", numberRowStr);
    for(int ix=0;ix<numberRow;ix++)
    {
        QString nRow=QString::number(ix);
        QString dataRow="";
        RowData* rd = m_MFATableModel->getDatainRow(ix);
        for(int iy=0;iy<m_MFATableModel->columnCount();iy++)
        {
            dataRow=dataRow+rd->getData(iy)+" ";
        }
        stream.writeTextElement("nRow", dataRow);
    }
    stream.writeEndElement(); // modules

    /* save frame */
    stream.writeStartElement("frames");
    numberRow = m_frameTableModel->rowCount();
    numberRowStr = QString::number(numberRow);
    stream.writeAttribute("nFrames", numberRowStr);

    for(int ix=0;ix<numberRow;ix++)
    {
        stream.writeStartElement("itemFrame");

        RowData* rd = m_frameTableModel->getDatainRow(ix);
        QString IdFrame = rd->getData(1);
        QString nModFrame = rd->getData(2);
        QString nameFrame = rd->getData(3);

        stream.writeAttribute("ID", IdFrame);
        stream.writeAttribute("nModFrame", nModFrame);
        stream.writeAttribute("name", nameFrame);

        MFATableModel* m  = m_frameTableModel->getModel(ix);
        int nModuleInFrame = m->rowCount();

        for(int iy=0;iy<nModuleInFrame;iy++)
        {
            QString dataRow="";
            RowData* rd2 = m->getDatainRow(iy);
            dataRow=dataRow+rd2->getData(1)+" ";
            dataRow=dataRow+rd2->getData(2)+" ";
            dataRow=dataRow+rd2->getData(3)+" ";

            stream.writeTextElement("RowModFrm", dataRow);
        }
        stream.writeEndElement();
    }
    stream.writeEndElement(); // frames

    /* save anim */
    stream.writeStartElement("anims");
    numberRow = m_animTableModel->rowCount();
    numberRowStr = QString::number(numberRow);
    stream.writeAttribute("nAnims", numberRowStr);

    for(int ix=0;ix<numberRow;ix++)
    {
        stream.writeStartElement("itemAnim");

        RowData* rd = m_animTableModel->getDatainRow(ix);
        QString IdAnim = rd->getData(1);
        QString nFrmAnim = rd->getData(2);
        QString nameAnim = rd->getData(3);

        stream.writeAttribute("ID", IdAnim);
        stream.writeAttribute("nAnimFrame", nFrmAnim);
        stream.writeAttribute("name", nameAnim);

        MFATableModel* m  = m_animTableModel->getModel(ix);
        int nFrameAnim = m->rowCount();

        for(int iy=0;iy<nFrameAnim;iy++)
        {
            QString dataRow="";
            RowData* rd2 = m->getDatainRow(iy);
            dataRow=dataRow+rd2->getData(1)+" ";
            dataRow=dataRow+rd2->getData(2)+" ";
            dataRow=dataRow+rd2->getData(3)+" ";
            dataRow=dataRow+rd2->getData(4)+" ";

            stream.writeTextElement("RowFrmAnim", dataRow);
        }
        stream.writeEndElement();
    }
    stream.writeEndElement(); // Anims

    //end
    stream.writeEndDocument();
 }

 void MainWindow::openDataSprite()
 {
     openDataSprite("");
 }

 void MainWindow::openDataSprite(QString path) // todo : separate this to other class
 {
     ui->tabWidget->setCurrentIndex(Page::MODULE);

     if(!path.compare("")){
        m_SprfileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
     } else {
        m_SprfileName = path;
     }
     if (!m_SprfileName.isEmpty())
     {
        /* clear all data */
        resetDataTable();

        QFile* file = new QFile(m_SprfileName);

        if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::critical(this,
                               "Xedithor: parsing XML sprite",
                               "Couldn't open "+m_SprfileName,
                               QMessageBox::Ok);
            m_SprfileName="";
            return;
        }
        QXmlStreamReader xml(file);
        while(!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if(token == QXmlStreamReader::StartDocument)
            {
                continue;
            }
            if(token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "sprites")
                {
                    continue;
                }
                if(xml.name() == "image")
                {
                    xml.readNext();
                    xml.readNext();
                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                    {

                        if(xml.name() == "path")
                        {
                           xml.readNext();
                           /* open image */
                           m_ImgfileName = xml.text().toString();
                           QImage image(m_ImgfileName);
                           if (image.isNull())
                           {
                               // if null, give another try to open
                               // supposed in same dir w/ .xml file
                               QFileInfo sprInfo(m_SprfileName);
                               QFileInfo _imgFI(m_ImgfileName);
                               QString imgFileName = _imgFI.fileName();

                               QString sprDir = sprInfo.dir().absolutePath();
                               QString supposedDirImg =sprDir +"/"+imgFileName;
                               m_ImgfileName = supposedDirImg;

                               image.load(m_ImgfileName);
                               if (image.isNull()) {
                                QMessageBox::information(this, tr("Xedithor"),
                                                         tr("Cannot load %1.").arg(m_ImgfileName));
                               }
                           }

                           pixmapOpened =QPixmap::fromImage(image);
                           editWindow->imageLabel->setImageGraphicsItem(&pixmapOpened);
                           editWindow->scaleFactor = 1.0;
                           //printAct->setEnabled(true);
                           //update info path image
                           ui->imagePathInfo->setText(m_ImgfileName);
                           /*end open image */
                        }
                    }
                }
                if(xml.name() == "modules")
                {
                    xml.readNext();
                    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                            xml.name() == "modules"))
                    {
                        if(xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if(xml.name() == "nRow")
                            {
                                xml.readNext();
                                parseDataRow(xml.text().toString());
                            }
                        }
                        xml.readNext();
                    }
                }
                if(xml.name() == "frames")
                {
                    xml.readNext();
                    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                            xml.name() == "frames"))
                    {
                        if(xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if(xml.name() == "itemFrame")
                            {
                                QList<QString> header;
                                QList<QString> body;

                                header.push_back(xml.attributes().at(0).value().toString());
                                header.push_back(xml.attributes().at(1).value().toString());
                                header.push_back(xml.attributes().at(2).value().toString());

                                while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                                        xml.name() == "itemFrame"))
                                {
                                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                                    {
                                        if(xml.name() == "RowModFrm")
                                        {
                                            xml.readNext();
                                            body.push_back(xml.text().toString());
                                        }
                                    }
                                    xml.readNext();
                                }
                                parseDataRowFrame(header,body);
                            }
                        }
                        xml.readNext();
                    }
                }
                if(xml.name() == "anims")
                {
                    xml.readNext();
                    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                            xml.name() == "anims"))
                    {
                        if(xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if(xml.name() == "itemAnim")
                            {
                                QList<QString> header;
                                QList<QString> body;

                                header.push_back(xml.attributes().at(0).value().toString());
                                header.push_back(xml.attributes().at(1).value().toString());
                                header.push_back(xml.attributes().at(2).value().toString());
                                //header.push_back(xml.attributes().at(3).value().toString());

                                while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                                        xml.name() == "itemAnim"))
                                {
                                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                                    {
                                        if(xml.name() == "RowFrmAnim")
                                        {
                                            xml.readNext();
                                            body.push_back(xml.text().toString());
                                        }
                                    }
                                    xml.readNext();
                                }
                                parseDataRowAnim(header,body);
                            }
                        }
                        xml.readNext();
                    }
                }
            }
        }
        if(xml.hasError())
        {
            QMessageBox::critical(this,
                                  "Xedithor: parsing XML sprite",
                                  "Xedithor: wrong formated sprite file",
                                  QMessageBox::Ok);
            m_SprfileName="";
        }
        xml.clear();
     }
 }

 void MainWindow::resetDataTable()
 {
     /* reset module table */
     m_MFATableModel->clearData();
     /* reset frame table */
     m_frameTableModel->clearData();
     /* reset anim table */
     m_animTableModel->clearData();
 }

 void MainWindow::parseDataRow(QString strDataRow)
 {
    UID::Instance().setAutoInc(false);
     /* create row */
    m_MFATableModel->insertRow(m_MFATableModel->rowCount());
    /* parse data row */
    QList<QString> datRow;
    QString buff="";
    QChar chSpace = QChar::fromAscii(' ');
    for(int i=0;i<strDataRow.count();i++)
    {
        QChar ch = strDataRow.at(i);
        if(ch!=chSpace)
        {
            buff+=ch;
        }
        else
        {
            datRow.insert(i,buff);
            buff="";
        }
    }
    /* set data row */
    RowData* rd = m_MFATableModel->getDatainRow(m_MFATableModel->rowCount()-1);

    for(int i= 0; i < datRow.count(); i++)
    {
        rd->setData(i,datRow.at(i));
    }
    /* set last ID */
    int lastID_= UID::Instance().getLastUID(UIDType::MODULE);
    int newrowID_  = rd->getData(1).toInt() - C_UID::MODULE_START;
    if( lastID_ <= newrowID_){ // 1 = uid module
        UID::Instance().setLastUID(newrowID_+1,UIDType::MODULE);
    }
    UID::Instance().setAutoInc(true);
 }

 void MainWindow::parseDataRowFrame(QList<QString>&header,QList<QString>&body)
 {
    UID::Instance().setAutoInc(false);
    m_frameTableModel->insertRow(m_frameTableModel->rowCount());
    /* set data row */
    int rowNow = m_frameTableModel->rowCount()-1;
    RowData* rd = m_frameTableModel->getDatainRow(rowNow);
    rd->setData(1,header.at(0));
    rd->setData(2,header.at(1));
    rd->setData(3,header.at(2));

    /* set sub Model */
    MFATableModel* _model_frame = m_frameTableModel->getModel(rowNow);

    int idC =0;
    QList<QString> datRow;
    foreach(QString str,body){
        QString strDataRow = str;
        QString buff="";
        QChar chSpace = QChar::fromAscii(' ');
        for(int i=0;i<strDataRow.count();i++)
        {
            QChar ch = strDataRow.at(i);
            if(ch!=chSpace)
            {
                buff+=ch;
            }
            else
            {
                datRow.insert(i,buff);
                buff="";
            }
        }

        _model_frame->insertRow(_model_frame->rowCount());
        int r = _model_frame->rowCount();

        RowData* rd2 = _model_frame->getDatainRow(r-1);

        rd2->setData(0,QString::number(idC));
        rd2->setData(1,datRow.at(0));
        rd2->setData(2,datRow.at(1));
        rd2->setData(3,datRow.at(2));

        datRow.clear();

        idC++;
        /* set last ID */
        int lastID_= UID::Instance().getLastUID(UIDType::FRAME_DESC);
        if( lastID_ <= idC){ // 1 = uid module
            UID::Instance().setLastUID(idC+1,UIDType::FRAME_DESC);
        }
    }

    /* set last ID */
    int lastID_= UID::Instance().getLastUID(UIDType::FRAME);
    int newrowID_  = rd->getData(1).toInt() - C_UID::FRAME_START;
    if( lastID_ <= newrowID_){ // 1 = uid module
        UID::Instance().setLastUID(newrowID_+1,UIDType::FRAME);
    }
    _model_frame->refresh();

    UID::Instance().setAutoInc(true);
 }

 void MainWindow::parseDataRowAnim(QList<QString>&header,QList<QString>&body)
 {
    UID::Instance().setAutoInc(false);

    m_animTableModel->insertRow(m_animTableModel->rowCount());
    /* set data row */
    int rowNow = m_animTableModel->rowCount()-1;
    RowData* rd = m_animTableModel->getDatainRow(rowNow);
    rd->setData(1,header.at(0));
    rd->setData(2,header.at(1));
    rd->setData(3,header.at(2));


    /* set sub Model */
    MFATableModel* _model_frame = m_animTableModel->getModel(rowNow);

    int idC =0;
    QList<QString> datRow;
    foreach(QString str,body){

        QString strDataRow = str;
        QString buff="";
        QChar chSpace = QChar::fromAscii(' ');
        for(int i=0;i<strDataRow.count();i++)
        {
            QChar ch = strDataRow.at(i);
            if(ch!=chSpace)
            {
                buff+=ch;
            }
            else
            {
                datRow.insert(i,buff);
                buff="";
            }
        }

        _model_frame->insertRow(_model_frame->rowCount());
        int r = _model_frame->rowCount();

        RowData* rd2 = _model_frame->getDatainRow(r-1);

        rd2->setData(0,QString::number(idC));
        rd2->setData(1,datRow.at(0));
        rd2->setData(2,datRow.at(1));
        rd2->setData(3,datRow.at(2));
        if(datRow.count()<4)      // this is previous format saving file
            rd2->setData(4,"1");  // ensure format doesn't break
        else
            rd2->setData(4,datRow.at(3));

        datRow.clear();

        idC++;
        // set last ID
        int lastID_= UID::Instance().getLastUID(UIDType::ANIM_DESC);
        if( lastID_ <= idC){ // 1 = uid module
            UID::Instance().setLastUID(idC+1,UIDType::ANIM_DESC);
        }
    }

    /* set last ID */
    int lastID_= UID::Instance().getLastUID(UIDType::ANIM);
    int newrowID_  = rd->getData(1).toInt() - C_UID::ANIM_START;
    if( lastID_ <= newrowID_){ // 1 = uid module
        UID::Instance().setLastUID(newrowID_+1,UIDType::ANIM);
    }
    _model_frame->refresh();

    UID::Instance().setAutoInc(true);
 }

 void MainWindow::TableDoubleClicked(const QModelIndex &index)
 {
     std::cout<<"TableDoubleClicked Row: "<<index.row()<<std::endl;
     std::cout<<"TableDoubleClicked Col: "<<index.column()<<std::endl;
 }

 void MainWindow::timerHit()
 {
     m_timer->stop();
     //if tab frame   // check valid frame (use valid module)
     MFATableModel* _model_frame  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
     MFATableModel* _sub_model_frame;

     for(int i=0;i<_model_frame->rowCount();i++)
     {
         RowData* _rowdataFrame = _model_frame->getDatainRow(i);
         _sub_model_frame = _model_frame->getModel(i);
         for(int j=0;j<_sub_model_frame->rowCount();j++)
         {
            RowData* _rowdata = _sub_model_frame->getDatainRow(j);
            QString _moduleID = _rowdata->getData(1);
            if(editWindow->modulesList->getItemByText(_moduleID) == NULL) {
                _rowdataFrame->setValid(false);
                _rowdata->setValid(false);
            }
            else{
                _rowdataFrame->setValid(true);
                _rowdata->setValid(true);
            }
         }
     }
     _model_frame->refresh();
     // end if tab frame
}

// offseting to 0,0
void MainWindow::reOffsetFrames()
{
     MFATableModel* _model_frame  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
     MFATableModel* _sub_model_frame;

     for(int i=0;i<_model_frame->rowCount();i++)
     {
         RowData* _rowdataFrame = _model_frame->getDatainRow(i);
         _sub_model_frame = _model_frame->getModel(i);

         // calc x min, y min
         int Xmin=65000,Ymin=65000;
         for(int j=0;j<_sub_model_frame->rowCount();j++)
         {
            RowData* _rowdata = _sub_model_frame->getDatainRow(j);
            int _offsetX      = _rowdata->getData(2).toInt();
            int _offsetY      = _rowdata->getData(3).toInt();
            if(Xmin > _offsetX)
                Xmin = _offsetX;
            if(Ymin > _offsetY)
                Ymin = _offsetY;
         }
         // re-offset
         for(int j=0;j<_sub_model_frame->rowCount();j++)
         {
            RowData* _rowdata = _sub_model_frame->getDatainRow(j);
            int _offsetX      = _rowdata->getData(2).toInt();
            int _offsetY      = _rowdata->getData(3).toInt();
            _rowdata->setData(2,QString::number(_offsetX - Xmin) );
            _rowdata->setData(3,QString::number(_offsetY - Ymin) );
         }
         _sub_model_frame->refresh();
     }
 }

int MainWindow::silentExportSprite(int i)
{
    reOffsetFrames();
    QString exportOutBin      = m_workingExportOutDir+"/"+QString::number(i)+".bin";
    QString texturePackerPath = QApplication::applicationDirPath()+"/extbin/texturepacker.jar";
    int formatExport          = 0;

    MFATableModel* _moduleModel = static_cast<MFATableModel*>(ui->mt_tableView1->model());
    MFATableModel* _frameModel  = static_cast<MFATableModel*>(ui->ft_tableView1->model());
    MFATableModel* _animModel   = static_cast<MFATableModel*>(ui->at_tableView1->model());

    SpriteExporter exporter(this->pixmapOpened,
                            _moduleModel,
                            _frameModel,
                            _animModel,
                            formatExport);
    exporter.setTexturePackerPath(texturePackerPath);
    exporter.setExportOutPath(exportOutBin);
    exporter.setImgSrcPath(this->m_ImgfileName);
    exporter.setExportOutSrcPath(m_exportSrcDir);
    exporter.setPackageName(m_packageName);

    QFileInfo fi(this->m_SprfileName);
    QString name = fi.baseName();
    exporter.setSprName(name);
    int checkExport = exporter.DoExporting();

    if(checkExport != 0) {
        std::cout<<"Error when exporting "<<checkExport<<std::endl;
    }
    return checkExport;
}


void MainWindow::setupSpriteManager()
{
    QFrame* frame = new QFrame(this);
    frameUI.setupUi(frame);

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    ui->mainToolBar->addWidget(spacerWidget);
    ui->mainToolBar->addWidget(frame);

    if(m_workingDir!="")
        spriteListRefresh();

    connect(frameUI.comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(openSpriteFromIndex(int)));
    connect(frameUI.tbRefresh,SIGNAL(clicked()),this,SLOT(spriteListRefresh()));
    connect(frameUI.tbExportAll,SIGNAL(clicked()),this,SLOT(exportAll()));
    connect(frameUI.tbworkDir,SIGNAL(clicked()),this,SLOT(setWorkDir()));
}

void MainWindow::openSpriteFromIndex(int index,bool generate)
{
    QString strOpenSprite = frameUI.comboBox->itemText( index);
    if(!(strOpenSprite =="--List Sprites--" || strOpenSprite ==""))
    {
        QString strOpenSpritePath = m_workingDir+"/"+strOpenSprite;
        openDataSprite(strOpenSpritePath);
        frameUI.comboBox->setCurrentIndex(0);

        if(generate)
        {
            PageTabChanged(Page::FRAME);
            PageTabChanged(Page::ANIM);

            QDir dirTempImg(m_workingExportOutDir);
            dirTempImg.mkpath("frames");
            dirTempImg.mkpath("anims");

            // save img from frames
            for(int i=0;i<m_ListPxmap.count();i++)
            {
                QString nameImgSave = QString::number(index)+"_F_"+m_ListStrFrameID.at(i)+".png";
                QPixmap imgSave     = m_ListPxmap.at(i);
                imgSave.save(m_workingExportOutDir+"\\frames\\"+nameImgSave,0,-1);

                // std::cout<<"save: "<<nameImgSave.toStdString().c_str()<<std::endl;
            }
            // save img from anims
            MFATableModel* _animModel   = static_cast<MFATableModel*>(ui->at_tableView1->model());
            int numberRow = _animModel->rowCount();

            for(int ix=0;ix<numberRow;ix++)
            {
               RowData* rd  = _animModel->getDatainRow(ix);
               int IdAnim      = rd->getData(1).toInt();
               QString animName =QString::number(IdAnim)+"_"+rd->getData(3);

               MFATableModel* m  = _animModel->getModel(ix);
               int nFrameAnim = m->rowCount();

               if(nFrameAnim>0)
               {
                   RowData* rd2 = m->getDatainRow(0);
                   int FrmID        =rd2->getData(1).toInt();

                   for(int i=0;i<m_ListPxmap.count();i++)
                   {
                       if(FrmID == m_ListStrFrameID.at(i).toInt())
                       {
                           QString nameImgSave = QString::number(index)+"_A_"+animName+".png";
                           QPixmap imgSave     = m_ListPxmap.at(i);
                           imgSave.save(m_workingExportOutDir+"\\anims\\"+nameImgSave,0,-1);
                       }
                   }
               }
            }
        }
   }
}

void MainWindow::spriteListRefresh()
{
    if(m_workingDir!="") {
        QStringList filterFileStr;
        filterFileStr.append("*.xml");
        QDir workingDir(m_workingDir);
        QStringList listSpriteNames = workingDir.entryList(filterFileStr,QDir::Files,QDir::Name);
        listSpriteNames.insert(0,"--List Sprites--");
        frameUI.comboBox->clear();
        for(int i=0;i<listSpriteNames.count();i++){
            frameUI.comboBox->addItem(listSpriteNames.at(i));
        }
    }
}

QString MainWindow::removeFileExtension(QString fileName)
{
    QChar ch;
    QString _result="";
    int i=0;
    while( 1 )
    {
        ch = fileName.at(i++);
        if(ch != QChar::fromAscii('.') )
            _result+=ch;
        else
            break;
    }
    return _result;
}

int MainWindow::exportAllSilent()
{
    m_silenExport=true;
    exportAll();
    m_silenExport=false;

    QApplication::exit();
    return 0;
}

void MainWindow::exportAll()
{
    if(m_workingDir!="" || m_workingExportOutDir!="") {

        QProgressDialog progress("Exporting files...", "", 0, frameUI.comboBox->count(), this);
        progress.setWindowModality(Qt::WindowModal);
        if(!m_silenExport) {
            progress.show();
        } else {
            std::cout<<" ..Xedithor: exporting sprites.."<<std::endl;
        }
        const int totalSprite = frameUI.comboBox->count();
        int errCode [256];// assume max sprite is 256
        for(int i=0;i<totalSprite;i++)
        {
            if(frameUI.comboBox->itemText(i) !="--List Sprites--") {
                if(!m_silenExport) {
                    progress.setValue(i);
                } else {
                    double processPercent = (((i*100.0f)/totalSprite));
                    std::cout<<"..export "<<processPercent<<" % "<<std::endl;
                }
                openSpriteFromIndex(i,true);
                errCode[i] = silentExportSprite(i);
            }
        }
        QMessageBox msg;
        QString strReport = "Exporting finished";
        strReport +="\nOutput Data Directory: "+this->m_workingExportOutDir+"\n";
        strReport +="\nOutput Src Directory : "+this->m_exportSrcDir+"\n";
        strReport +="\nError when export:";

        bool allsuccess=true;
        // create interface
        QFile file(m_exportSrcDir+"/DATA_SPRITE.java");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream interfaceText(&file);

        interfaceText<<"// <-- This file is generated by xedithor. Don't edit this --> "<<"\n"<<"\n";
        interfaceText<<m_packageName<<";"<<"\n"<<"\n";
        interfaceText<<"interface DATA_SPRITE"<<"\n";
        // open brace interface
        interfaceText<<"{"<<"\n";
        int intercafeValue=0;
        int totError =0;
        for(int i=0;i<frameUI.comboBox->count();i++)
        {
            if(errCode[i]){
                strReport +="\n -"+frameUI.comboBox->itemText(i);
                allsuccess=false;
                intercafeValue++;
                totError++;
                interfaceText <<"// ----- error export: "<<frameUI.comboBox->itemText(i)<<"\n";
            }
            else {
                QString strSprName = frameUI.comboBox->itemText(i);
                if(strSprName != "--List Sprites--"){
                    QFileInfo fi(strSprName);
                    QString name = fi.baseName();
                    name = name.toUpper();
                    interfaceText <<"	public final static int SPR_" << name <<" = "<<intercafeValue<<";"<<"\n";
                    //intercafeValue++;
                }
                intercafeValue++;
            }

        }
        interfaceText <<"	public final static int COUNT" << " = "<<(intercafeValue-totError)<<";"<< "\n";
        //close brace interface
        interfaceText<<"}"<<"\n";
        file.close();
        if(allsuccess)
            strReport +="\nNo Error, all success exported";
        if(!m_silenExport) {
            msg.setText(strReport);
            msg.exec();
        } else {
            std::cout<<"..export is done.."<<std::endl;
            std::cout<<strReport.toStdString().c_str()<<std::endl;
        }

    }
    else {
        QMessageBox msg;
        msg.setText("for export all, please set working directory and export output directory");
        msg.exec();
        setWorkDir();
    }
}

void MainWindow::setWorkDir()
{
    SetWorkDirDialog* setDirDlg = new SetWorkDirDialog(this);
    setDirDlg->setPrevWorkDirPath(m_workingDir,m_workingExportOutDir,m_exportSrcDir,m_packageName);
    int retValue = setDirDlg->exec();

    if(retValue == QDialog::Accepted)
    {
        m_workingDir          = setDirDlg->getWorkDir();
        m_workingExportOutDir = setDirDlg->getExportDir();
        m_exportSrcDir        = setDirDlg->getExportSrcDir();
        m_packageName         = setDirDlg->getPackageName();

        spriteListRefresh();
        AppConfig::getInstance()->saveWorkingDir(m_workingDir,
                                                 m_workingExportOutDir,
                                                 m_exportSrcDir,
                                                 m_packageName);
    }
    delete setDirDlg;
    setDirDlg=NULL;
}
// create some shorcut
// yeah, best way is inherited table view to capture key, this is not elegant
void MainWindow::shorcutSetup()
{
    //----- module
    // clone module
    QShortcut* shortcutCloneModule = new QShortcut(tr("Ctrl+C"), ui->mt_tableView1);
    connect(shortcutCloneModule, SIGNAL(activated()), this, SLOT(cloneModuleShorcut()));
    // up module
    QShortcut* shortcutUp = new QShortcut(Qt::Key_Up, ui->mt_tableView1);
    connect(shortcutUp, SIGNAL(activated()), this, SLOT(arrowUpModuleShorcut()));
    // down module
    QShortcut* shortcutDown = new QShortcut(Qt::Key_Down, ui->mt_tableView1);
    connect(shortcutDown, SIGNAL(activated()), this, SLOT(arrowDownModuleShorcut()));

    //----- frame
    // up frame
    QShortcut* shortcutUp_f = new QShortcut(Qt::Key_Up, ui->ft_tableView1);
    connect(shortcutUp_f, SIGNAL(activated()), this, SLOT(arrowUpFrameShorcut()));
    // down frame
    QShortcut* shortcutDown_f = new QShortcut(Qt::Key_Down, ui->ft_tableView1);
    connect(shortcutDown_f, SIGNAL(activated()), this, SLOT(arrowDownFrameShorcut()));
    /*
    //----- frame desc
    // up frame desc
    QShortcut* shortcutUp_fd = new QShortcut(Qt::Key_Up, ui->ft_tableView2);
    connect(shortcutUp_fd, SIGNAL(activated()), this, SLOT(arrowUpFrameDescShorcut()));
    // down frame desc
    QShortcut* shortcutDown_fd = new QShortcut(Qt::Key_Down, ui->ft_tableView2);
    connect(shortcutDown_fd, SIGNAL(activated()), this, SLOT(arrowDownFrameDescShorcut()));
    */
    //----- anim
    // up anim
    QShortcut* shortcutUp_a = new QShortcut(Qt::Key_Up, ui->at_tableView1);
    connect(shortcutUp_a, SIGNAL(activated()), this, SLOT(arrowUpAnimShorcut()));
    // down anim
    QShortcut* shortcutDown_a = new QShortcut(Qt::Key_Down, ui->at_tableView1);
    connect(shortcutDown_a, SIGNAL(activated()), this, SLOT(arrowDownAnimShorcut()));
    /*
    //----- anim desc
    // up anim desc
    QShortcut* shortcutUp_ad = new QShortcut(Qt::Key_Up, ui->at_tableView2);
    connect(shortcutUp_ad, SIGNAL(activated()), this, SLOT(arrowUpAnimDescShorcut()));
    // down anim desc
    QShortcut* shortcutDown_ad = new QShortcut(Qt::Key_Down, ui->at_tableView2);
    connect(shortcutDown_ad, SIGNAL(activated()), this, SLOT(arrowDownAnimDescShorcut()));
    */

}

void MainWindow::cloneModuleShorcut()
{
    tableCloneRow(ui->mt_tableView1);
}

void MainWindow::arrowUpModuleShorcut()
{
    this->tableUpSel(ui->mt_tableView1);
    int currRow= ui->mt_tableView1->currentIndex().row();
    moduleTableRowSelected(currRow);
}

void MainWindow::arrowDownModuleShorcut()
{
    this->tableDownSel(ui->mt_tableView1);
    int currRow= ui->mt_tableView1->currentIndex().row();
    moduleTableRowSelected(currRow);
}
// frame
void MainWindow::arrowUpFrameShorcut()
{
    this->tableUpSel(ui->ft_tableView1);
    int currRow= ui->ft_tableView1->currentIndex().row();
    frameTableRowSelected(currRow);
}

void MainWindow::arrowDownFrameShorcut()
{
    this->tableDownSel(ui->ft_tableView1);
    int currRow= ui->ft_tableView1->currentIndex().row();
    frameTableRowSelected(currRow);
}

// frame desc
void MainWindow::arrowDownFrameDescShorcut()
{
    this->tableDownSel(ui->ft_tableView2);
    int currRow= ui->ft_tableView2->currentIndex().row();
    frameDescTableRowSelected(currRow);
}

void MainWindow::arrowUpFrameDescShorcut()
{
    this->tableUpSel(ui->ft_tableView2);
    int currRow= ui->ft_tableView2->currentIndex().row();
    frameDescTableRowSelected(currRow);
}

// anim
void MainWindow::arrowDownAnimShorcut()
{
    this->tableDownSel(ui->at_tableView1);
    int currRow= ui->at_tableView1->currentIndex().row();
    animTableRowSelected(currRow);
}

void MainWindow::arrowUpAnimShorcut()
{
    this->tableUpSel(ui->at_tableView1);
    int currRow= ui->at_tableView1->currentIndex().row();
    animTableRowSelected(currRow);
}

// anim desc
void MainWindow::arrowDownAnimDescShorcut()
{
    this->tableDownSel(ui->at_tableView2);
    int currRow= ui->at_tableView2->currentIndex().row();
    animDescTableRowSelected(currRow);
}

void MainWindow::arrowUpAnimDescShorcut()
{
    this->tableUpSel(ui->at_tableView2);
    int currRow= ui->at_tableView2->currentIndex().row();
    animDescTableRowSelected(currRow);
}




