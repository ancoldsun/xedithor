
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uidmanager.h"


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

    //m_toolDialog = new QDialog(this);
    //toolDialogFrm.setupUi(m_toolDialog);

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

    printAct = new QAction(QIcon(":/images/paste.png"),tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(QIcon(":/images/new.png"),tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // tool

    toolFrameAct = new QAction(QIcon(":/images/Calculator.png"),tr("&Frame"), this);
    //toolFrameAct->setShortcuts(QKeySequence::Save);
    //toolFrameAct->setStatusTip(tr("Save the document to disk"));
    connect(toolFrameAct, SIGNAL(triggered()), this, SLOT(showToolDialog()));

    // open image button
    connect(ui->openImageButton, SIGNAL(clicked()), this, SLOT(open()));
}

void MainWindow::CreateMainMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File  "));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit  "));

    toolMenu = menuBar()->addMenu(tr("&Tool  "));
    toolMenu->addAction(toolFrameAct);

    helpMenu = menuBar()->addMenu(tr("&Help  "));
    //
}

void MainWindow::CreateToolBar()
{
    ui->mainToolBar->addAction(newAct);
    ui->mainToolBar->addAction(openAct);
    ui->mainToolBar->addAction(saveAct);
    ui->mainToolBar->addAction(printAct);
}

void MainWindow::SetupTables()
{
    /* module */
    m_moduleTableModel = new ModuleTableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new ModuleRowDataHandler());
    m_moduleTableModel->AddEditableColumn(2);
    m_moduleTableModel->AddEditableColumn(3);
    m_moduleTableModel->AddEditableColumn(4);
    m_moduleTableModel->AddEditableColumn(5);
    ui->mt_tableView1->setModel(m_moduleTableModel);
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
    m_frameTableModel = new ModuleTableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new FrameRowDataHandler());
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
    m_frameDescTableModel = new ModuleTableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new FrameDescRowDataHandler());
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
    m_animTableModel = new ModuleTableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new AnimRowDataHandler());
    m_animTableModel->setHasModel(true);
    m_animTableModel->setSubModelRowHandler(new AnimDescRowDataHandler());
    ui->at_tableView1->setModel(m_animTableModel);
    ui->at_tableView1->setSelectionBehavior(QTableView::SelectRows);
    m_animTableModel->AddEditableColumn(3);

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->at_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->at_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->at_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));

    //frame anim
    m_animDescTableModel = new ModuleTableModel(this,SETUPTABLE::RowCount,SETUPTABLE::ColCount,new AnimDescRowDataHandler());
    ui->at_tableView2->setModel(m_animDescTableModel);
    ui->at_tableView2->setSelectionBehavior(QTableView::SelectRows);

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
        printAct->setEnabled(true);
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

void MainWindow::print()
{

}

void MainWindow::showToolDialog()
{
    //int returnModal = m_toolDialog->exec();
   // std::cout<<"returnModal.."<<returnModal<<std::endl;
}

//table button clicked
void MainWindow::Add_Clicked()
{
    QWidget *sender = (QWidget *) QObject::sender();
    std::cout<<"ADD.."<<sender->objectName().toStdString()<<std::endl;

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
    std::cout<<"CLONE.."<<std::endl;
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
    std::cout<<"DEL.."<<std::endl;
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
            ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->ft_tableView2->model());
            RowData* rd = m->getDatainRow(row_);
            int id_ =rd->getData(0).toInt();
            std::cout<<"id deleted..: "<<id_<<std::endl;
            editWindow->imageLabel->DeletePixmapItem(id_);
            /* end del */

            /* update module frame count */
            row_ = ui->ft_tableView1->currentIndex().row();
            std::cout<<"row_ deleted..: "<<row_<<std::endl;
            if(row_ == -1){
                row_ = 0;
            }
            m = static_cast<ModuleTableModel*>(ui->ft_tableView1->model());
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
        tableDelRow(ui->at_tableView2);
    }
}

void MainWindow::Up_Clicked()
{
    std::cout<<"UP.."<<std::endl;
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
    std::cout<<"DOWN.."<<std::endl;
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
    std::cout<<"TOP.."<<std::endl;
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
    std::cout<<"BOTTOM.."<<std::endl;
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

   ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
   table->model()->insertRow(m->rowCount());
   QModelIndex index = table->model()->index(newRow+1,0);
   table->setCurrentIndex(index);
   m->refresh();
}

void MainWindow::tableCloneRow(QTableView* table)
{
    int rowToClone = table->currentIndex().row();
    if(rowToClone !=-1)
    {
        ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
        m->cloneRow(rowToClone);
        QModelIndex index = table->model()->index(rowToClone+1,0);
        table->setCurrentIndex(index);
    }
}

void MainWindow::tableDelRow(QTableView* table)
{
    ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
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
        ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
        m->swapRow(currRow,--currRow);
        table->setCurrentIndex(table->model()->index(currRow , 0, QModelIndex()));
    }
}

void MainWindow::tableDownSel(QTableView* table)
{
    int currRow = table->currentIndex().row();

    ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
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
    ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());

    m->swapRow(currRow,0);
}

void MainWindow::tableBotSel(QTableView* table)
{
    ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
    int currRow = table->currentIndex().row();
    table->setCurrentIndex(table->model()->index(m->rowCount()-1 , 0, QModelIndex()));

    m->swapRow(currRow,m->rowCount()-1);
}

void MainWindow::tableRowSelected(const QModelIndex& index)
{
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_tableView1 ){   // table module

        int rowSelected_ = ui->mt_tableView1->currentIndex().row();
        std::cout<<"tableRowSelected Row: "<<rowSelected_<<std::endl;

        ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->mt_tableView1->model());
        RowData* rd = m->getDatainRow(rowSelected_);

        qreal px_ =rd->getData(2).toDouble();
        qreal py_ =rd->getData(3).toDouble();
        qreal w_  =rd->getData(4).toDouble();
        qreal h_  =rd->getData(5).toDouble();

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
    else if(sender == ui->ft_tableView1){   // table frame 1
        int rowSelected_ = ui->ft_tableView1->currentIndex().row();

        if(m_lastRowSelectedFT != rowSelected_)
        {
            m_lastRowSelectedFT = rowSelected_;
            std::cout<<"tableRowSelected Row: "<<rowSelected_<<std::endl;

            ModuleTableModel* mf = static_cast<ModuleTableModel*>(ui->ft_tableView1->model());
            ModuleTableModel* mf_bottom = mf->getModel(rowSelected_);
            ui->ft_tableView2->setModel(mf_bottom);
            // clear prev row images item
            editWindow->imageLabel->clearGraphPixmapItem();
            // create
            for(int i=0;i<mf_bottom->rowCount();i++)
            {
                std::cout<<"Row: "<<i<<" rc "<<mf_bottom->rowCount()<<std::endl;
                RowData* rd = mf_bottom->getDatainRow(i);
                std::cout<<"after Row: "<<i<<std::endl;

                int id_           = rd->getData(0).toInt();
                QString moduleID_ = rd->getData(1);
                int px_           = rd->getData(2).toInt();
                int py_           = rd->getData(3).toInt();
                //qreal w_    =rd->getData(4).toDouble();
                //qreal h_    =rd->getData(5).toDouble();

                QPixmap pixmap = editWindow->modulesList->getItemByText(moduleID_)->icon().pixmap(500,500);
                QPixmap copyPixmap = pixmap.copy();
                editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);

            }
        }
    } else if(sender == ui->ft_tableView2){ // table module-frame

        int rowSelected_ = ui->ft_tableView2->currentIndex().row();

        ModuleTableModel* mf = static_cast<ModuleTableModel*>(ui->ft_tableView2->model());
        RowData* _row_data          = mf->getDatainRow(rowSelected_);
        int id_                     = _row_data->getData(0).toInt();
        editWindow->imageLabel->setSelectedPixmapItem(id_);

    }  else if(sender == ui->at_tableView1){ // table anim

        if(editWindow->modulesList->count()>0)
        {
            int _rowSelected = ui->at_tableView1->currentIndex().row();
            ModuleTableModel* _anim_model       = static_cast<ModuleTableModel*>(ui->at_tableView1->model());
            ModuleTableModel* _frame_anim_model = _anim_model->getModel(_rowSelected);
            ui->at_tableView2->setModel(_frame_anim_model);

            // clear prev row images item
            editWindow->imageLabel->clearGraphPixmapItem();
            editWindow->createAnimation();
        }
    } else if(sender == ui->at_tableView2) {     // // table frame anim
        std::cout<<"----should be clear anim "<<std::endl;
        editWindow->imageLabel->clearAnimation();

        ModuleTableModel* frameAnimModel= static_cast<ModuleTableModel*>(ui->at_tableView2->model());

        // clear prev row images item
        editWindow->imageLabel->clearGraphPixmapItem();
        // create
        for(int i=0;i<frameAnimModel->rowCount();i++)
        {
             RowData* rd = frameAnimModel->getDatainRow(i);

            int id_           = rd->getData(0).toInt();
            QString moduleID_ = rd->getData(1);
            int px_           = rd->getData(2).toInt();
            int py_           = rd->getData(3).toInt();
            //qreal w_    =rd->getData(4).toDouble();
            //qreal h_    =rd->getData(5).toDouble();

            QPixmap pixmap = editWindow->modulesList->getItemByText(moduleID_)->icon().pixmap(500,500);
            QPixmap copyPixmap = pixmap.copy();
            editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);
        }
      }
}

void MainWindow::UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB)
{
    //todo:
    //std::cout<<"UpdateDataCell..........: "<<std::endl;
}

void MainWindow::TableEditCompleted(QString str)
{
    std::cout<<"data edit completed...........: "<<std::endl;
    int rowSelected_ = ui->mt_tableView1->currentIndex().row();

    ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->mt_tableView1->model());
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
     std::cout<<"page: "<<indexPage<<std::endl;

     if(indexPage== Page::MODULE)
     {
        editWindow->getModuleList()->clear();
        // set to modules table
        editWindow->imageLabel->m_table = ui->mt_tableView1;
        editWindow->imageLabel->m_table_bottom=NULL;
        editWindow->setupViewModule();//imageLabel->setupGraphViewModule();
     }
     else if(indexPage == Page::FRAME)
     {
         m_lastRowSelectedFT =-1;
         editWindow->getModuleList()->clear();
         ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->mt_tableView1->model());

         std::cout<<"Page::FRAME: "<<m->rowCount()<<std::endl;
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
         editWindow->setupViewFrame();//imageLabel->setupGraphViewFrame();

     }
     else if(indexPage == Page::ANIM)
     {
        ModuleTableModel* m  = static_cast<ModuleTableModel*>(ui->ft_tableView1->model());
        ModuleTableModel* m2;

        std::cout<<"sss: "<<editWindow->modulesList->count()<<std::endl;

        if(editWindow->modulesList->count()>0) {

            QList<QPixmap> listPxmap;
            QList<QString> listStrFrameID;
            //
            for(int i=0;i<m->rowCount();i++)
            {
                if(m->getDatainRow(i)->getData(2).toInt()>0)
                {
                    editWindow->imageLabel->clearGraphPixmapItem();
                    m2 = m->getModel(i);
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
                            QPixmap pixmap = _icon.pixmap(500,500);
                            QPixmap copyPixmap = pixmap.copy();
                            editWindow->imageLabel->AddPixmapItem(&copyPixmap,false,id_,px_,py_);
                        }
                    }
                    QPixmap pieceImage =QPixmap::fromImage((editWindow->imageLabel->exportToImage()));
                    listStrFrameID.push_back(m->getDatainRow(i)->getData(1));
                    listPxmap.push_back(pieceImage);
                }
            }
            editWindow->getModuleList()->clear();
            editWindow->imageLabel->clearGraphPixmapItem();

            for(int i=0;i<listPxmap.count();i++)
            {
                QPixmap _pixmap = listPxmap.at(i);
                editWindow->getModuleList()->addPiece(_pixmap,QPoint(0,0),listStrFrameID.at(i));
            }
            //QPixmap pieceImage =QPixmap::fromImage((editWindow->imageLabel->exportToImage()));
            //QPixmap pieceImage =pixmapOpened.copy(px_, py_, w_, h_);
        }

        //editWindow->getModuleList()->clear();
        editWindow->setupViewAnim();
        //editWindow->getModuleList()->addPiece(pieceImage,QPoint(0,0),0);
        // graph now handle frame table
        editWindow->imageLabel->m_table        = ui->at_tableView1;
        editWindow->imageLabel->m_table_bottom = ui->at_tableView2;

        editWindow->imageLabel->m_table_frame     = ui->ft_tableView1;
        editWindow->imageLabel->m_table_frameDesc = ui->ft_tableView2;

        editWindow->imageLabel->m_table_module   = ui->mt_tableView1;
     }
 }
 void MainWindow::saveDataSprite()
 {
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
    int numberRow = m_moduleTableModel->rowCount();
    QString numberRowStr = QString::number(numberRow);
    stream.writeAttribute("nModules", numberRowStr);
    for(int ix=0;ix<numberRow;ix++)
    {
        QString nRow=QString::number(ix);
        QString dataRow="";
        RowData* rd = m_moduleTableModel->getDatainRow(ix);
        for(int iy=0;iy<m_moduleTableModel->columnCount();iy++)
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

        ModuleTableModel* m  = m_frameTableModel->getModel(ix);
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

        ModuleTableModel* m  = m_animTableModel->getModel(ix);
        int nFrameAnim = m->rowCount();

        for(int iy=0;iy<nFrameAnim;iy++)
        {
            QString dataRow="";
            RowData* rd2 = m->getDatainRow(iy);
            dataRow=dataRow+rd2->getData(1)+" ";
            dataRow=dataRow+rd2->getData(2)+" ";
            dataRow=dataRow+rd2->getData(3)+" ";

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
     m_SprfileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
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
            std::cout<<"error open"<<std::endl;
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
                    //std::cout<<"image available"<<std::endl;
                    xml.readNext();
                    xml.readNext();
                    //std::cout<<"image available"<<xml.name().toString().toStdString().c_str()<<std::endl;
                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        //std::cout<<"--- 3 ---"<<std::endl;
                        if(xml.name() == "path")
                        {
                           xml.readNext();
                           //std::cout<<xml.text().toString().toStdString().c_str()<<std::endl;
                           /* open image */
                           m_ImgfileName = xml.text().toString();
                           QImage image(m_ImgfileName);
                           if (image.isNull()) {
                               QMessageBox::information(this, tr("Xedithor"),
                                                        tr("Cannot load %1.").arg(m_ImgfileName));
                           }

                           pixmapOpened =QPixmap::fromImage(image);
                           editWindow->imageLabel->setImageGraphicsItem(&pixmapOpened);
                           editWindow->scaleFactor = 1.0;
                           printAct->setEnabled(true);
                           //update info path image
                           ui->imagePathInfo->setText(m_ImgfileName);
                           /*end open image */
                        }
                    }
                }
                if(xml.name() == "modules")
                {
                    //std::cout<<"--- modules ---"<<std::endl;
                    //std::cout<<"nModules: "<<xml.attributes().data()->value().toString().toStdString().c_str()<<std::endl;
                    xml.readNext();
                    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                            xml.name() == "modules"))
                    {
                        if(xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if(xml.name() == "nRow")
                            {
                                //std::cout<<"--- nRow ---"<<std::endl;
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
            }
        }
        if(xml.hasError())
        {
            QMessageBox::critical(this,
                                  "Xedithor: parsing XML sprite",
                                  "Xedithor: wrong formated sprite file",
                                  QMessageBox::Ok);
        }
        xml.clear();
     }
 }

 void MainWindow::resetDataTable()
 {
     /* reset module table */
     m_moduleTableModel->clearData();
     /* reset frame table */
     m_frameTableModel->clearData();
     /* reset anim table */
     m_animTableModel->clearData();
 }

 void MainWindow::parseDataRow(QString strDataRow)
 {
    UID::Instance().setAutoInc(false);
     /* create row */
    m_moduleTableModel->insertRow(m_moduleTableModel->rowCount());
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
    RowData* rd = m_moduleTableModel->getDatainRow(m_moduleTableModel->rowCount()-1);

    for(int i= 0; i < datRow.count(); i++)
    {
        rd->setData(i,datRow.at(i));
    }
    /* set last ID */
    int lastID_= UID::Instance().getLastUID(UIDType::MODULE);
    int newrowID_  = rd->getData(1).toInt() - 1000;
    if( lastID_ <= newrowID_){ // 1 = uid module
        UID::Instance().setLastUID(newrowID_+1,UIDType::MODULE);
    }
    UID::Instance().setAutoInc(true);
 }

 void MainWindow::parseDataRowFrame(QList<QString>&header,QList<QString>&body)
 {
    UID::Instance().setAutoInc(false);
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"ID     :"<<header.at(0).toStdString().c_str()<<std::endl;
    std::cout<<"N      :"<<header.at(1).toStdString().c_str()<<std::endl;
    std::cout<<"Name   :"<<header.at(2).toStdString().c_str()<<std::endl;

    m_frameTableModel->insertRow(m_frameTableModel->rowCount());
    /* set data row */
    int rowNow = m_frameTableModel->rowCount()-1;
    RowData* rd = m_frameTableModel->getDatainRow(rowNow);
    rd->setData(1,header.at(0));
    rd->setData(2,header.at(1));
    rd->setData(3,header.at(2));

    /* set sub Model */
    ModuleTableModel* m = m_frameTableModel->getModel(rowNow);

    int idC =0;
    QList<QString> datRow;
    foreach(QString str,body){
        std::cout<<"---body: "<<str.toStdString().c_str()<<std::endl;
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

        m->insertRow(m->rowCount());
        int r = m->rowCount();

        RowData* rd2 = m->getDatainRow(r-1);

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
    int newrowID_  = rd->getData(1).toInt() - 3000;
    if( lastID_ <= newrowID_){ // 1 = uid module
        UID::Instance().setLastUID(newrowID_+1,UIDType::FRAME);
    }
    m->refresh();

    UID::Instance().setAutoInc(true);
 }

 void MainWindow::TableDoubleClicked(const QModelIndex &index)
 {
     std::cout<<"TableDoubleClicked Row: "<<index.row()<<std::endl;
     std::cout<<"TableDoubleClicked Col: "<<index.column()<<std::endl;
 }
