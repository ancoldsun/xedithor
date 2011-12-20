
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    // open image button
    connect(ui->openImageButton, SIGNAL(clicked()), this, SLOT(open()));
}

void MainWindow::CreateMainMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
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
    /*
    for(int i=0;i<XD::NUM_TAB;i++)
    {
        for(int j=0;j<XD::NUM_TABLE;j++)
        {
            // set column num, row num
            m_Atable[i][j]->setColumnCount(CMainWindow::COUNT_COLUMN_TABLE);
            m_Atable[i][j]->setRowCount(1);

             // set column width
            int width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
            for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
            {
                m_Atable[i][j]->setColumnWidth(m, width_col);
            }
            // set default table header
            m_Atable[i][j]->setHorizontalHeaderItem(0,new QTableWidgetItem("Index",0));
            m_Atable[i][j]->setHorizontalHeaderItem(1,new QTableWidgetItem("ID",1));
            m_Atable[i][j]->setHorizontalHeaderItem(2,new QTableWidgetItem("X",2));
            m_Atable[i][j]->setHorizontalHeaderItem(3,new QTableWidgetItem("Y",3));
            m_Atable[i][j]->setHorizontalHeaderItem(4,new QTableWidgetItem("Width",4));
            m_Atable[i][j]->setHorizontalHeaderItem(5,new QTableWidgetItem("Height",5));
        }
    }

    //setup default first row value
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,0,new QTableWidgetItem("0",0));
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,1,new QTableWidgetItem("1000",1));
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,2,new QTableWidgetItem("0",2));
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,3,new QTableWidgetItem("0",3));
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,4,new QTableWidgetItem("32",4));
    m_Atable[XD::T_MODULE][XD::TABLE1]->setItem(0,5,new QTableWidgetItem("32",5));

    */

    /* module */
    m_moduleTableModel = new ModuleTableModel(this,1,6,new ModuleRowDataHandler());
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

    editWindow->imageLabel->m_table = ui->mt_tableView1;

    /*frame - top table */
    m_frameTableModel = new ModuleTableModel(this,1,6,new FrameRowDataHandler());
    ui->ft_tableView1->setModel(m_frameTableModel);
    ui->ft_tableView1->setSelectionBehavior(QTableView::SelectRows);

    width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->ft_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->ft_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->ft_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));
    //connect(ui->ft_tableView1->model(),SIGNAL(editCompleted(QString)),this,SLOT(TableEditCompleted(QString)));

    /*frame - bottom table*/
    m_frameDescTableModel = new ModuleTableModel(this,1,6,new FrameDescRowDataHandler());
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

    /*
    //table
    m_Atable[XD::T_MODULE][XD::TABLE1] =ui->mt_tableWidget1;
    m_Atable[XD::T_MODULE][XD::TABLE2] =ui->mt_tableWidget2;
    m_Atable[XD::T_FRAME][XD::TABLE1]  =ui->ft_tableWidget1;
    m_Atable[XD::T_FRAME][XD::TABLE2]  =ui->ft_tableWidget2;
    m_Atable[XD::T_ANIM][XD::TABLE1]   =ui->at_tableWidget1;
    m_Atable[XD::T_ANIM][XD::TABLE2]   =ui->at_tableWidget2;
    */
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
     // table 2
     //connect(ui->mt_navTable2_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     //connect(ui->mt_navTable2_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     //connect(ui->mt_navTable2_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     //connect(ui->mt_navTable2_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     //connect(ui->mt_navTable2_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     //connect(ui->mt_navTable2_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     // connect(ui->mt_navTable2_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
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

     //doubleClicked ( const QModelIndex & index )

}

void MainWindow::newFile()
{

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
        tableDelRow(ui->ft_tableView2);
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
   std::cout<<"ROW: "<<table->currentIndex().row()<<std::endl;
   int newRow = table->currentIndex().row();
   if(newRow==-1)
       newRow=0;
   table->model()->insertRow(newRow);
   std::cout<<"ROW: "<<table->currentIndex().row()<<std::endl;
   ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
   m->refresh();
}

void MainWindow::tableCloneRow(QTableView* table)
{
    std::cout<<"ROW: "<<table->currentIndex().row()<<std::endl;

    int rowToClone = table->currentIndex().row();
    std::cout<<"ROW2: "<<table->currentIndex().row()<<std::endl;
    if(rowToClone !=-1)
    {
       std::cout<<"ROW3: "<<table->currentIndex().row()<<std::endl;
        ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
        std::cout<<"ROW4: "<<table->currentIndex().row()<<std::endl;
       m->cloneRow(rowToClone);
       std::cout<<"ROW5: "<<table->currentIndex().row()<<std::endl;
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
    if(sender == ui->mt_tableView1 ){   // table 1

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
    }
}

void MainWindow::UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB)
{
    //todo:
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
        editWindow->imageLabel->setupGraphViewModule();
     }
     else if(indexPage == Page::FRAME)
     {

         ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->mt_tableView1->model());

         std::cout<<"Page::FRAME: "<<m->rowCount()<<std::endl;
         editWindow->getModuleList()->clear();
         for(int i=0;i<m->rowCount();i++)
         {
             RowData* rd = m->getDatainRow(i);

             QString id_ ="mID-"+rd->getData(1);
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
         editWindow->imageLabel->m_table = ui->ft_tableView2;
         editWindow->imageLabel->setupGraphViewFrame();

     }
     else if(indexPage == Page::ANIM)
     {

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
    //todo:
    /* save anim */
    //todo:
    stream.writeEndElement(); // sprites
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
                               "QXSRExample::parseXML",
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
            }
        }
        if(xml.hasError())
        {
            QMessageBox::critical(this,
                                  "QXSRExample::parseXML",
                                  xml.errorString(),
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
     //todo:
     /* reset anim table */
     //todo:
 }

 void MainWindow::parseDataRow(QString strDataRow)
 {
    //std::cout<<" data row: "<<strDataRow.toStdString().c_str()<<std::endl;
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
    //std::cout<<" data row re "<<buff.toStdString().c_str()<<std::endl;
 }
