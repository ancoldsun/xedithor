
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
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

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

    m_moduleTableModel = new ModuleTableModel(this);
    ui->mt_tableView1->setModel(m_moduleTableModel);
    ui->mt_tableView1->setSelectionBehavior(QTableView::SelectRows);

    int width_col = CMainWindow::MIN_WIDTH_LEFT_DOCK / CMainWindow::COUNT_COLUMN_TABLE - 4;
    for(int m=0;m<CMainWindow::COUNT_COLUMN_TABLE;m++)
    {
        ui->mt_tableView1->setColumnWidth(m, width_col);
    }
    connect(ui->mt_tableView1, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableRowSelected(QModelIndex)));
    connect(ui->mt_tableView1->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(UpdateDataCell(QModelIndex,QModelIndex)));
    //editCompleted
    connect(ui->mt_tableView1->model(),SIGNAL(editCompleted(QString)),this,SLOT(TableEditCompleted(QString)));

    editWindow->imageLabel->m_table = ui->mt_tableView1;
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
     connect(ui->mt_navTable2_button1, SIGNAL(clicked()), this, SLOT(Add_Clicked()));
     connect(ui->mt_navTable2_button2, SIGNAL(clicked()), this, SLOT(Clone_Clicked()));
     connect(ui->mt_navTable2_button3, SIGNAL(clicked()), this, SLOT(Del_Clicked()));
     connect(ui->mt_navTable2_button4, SIGNAL(clicked()), this, SLOT(Up_Clicked()));
     connect(ui->mt_navTable2_button5, SIGNAL(clicked()), this, SLOT(Down_Clicked()));
     connect(ui->mt_navTable2_button6, SIGNAL(clicked()), this, SLOT(Top_Clicked()));
     connect(ui->mt_navTable2_button7, SIGNAL(clicked()), this, SLOT(Bottom_Clicked()));
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
}

void MainWindow::newFile()
{

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Xedithor"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        pixmapOpened =QPixmap::fromImage(image);
        editWindow->imageLabel->setImageGraphicsItem(&pixmapOpened);
        editWindow->scaleFactor = 1.0;
        printAct->setEnabled(true);
    }
}

bool MainWindow::save()
{
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
    /*
    else if(sender == ui->mt_navTable2_button1){
        tableAddRow(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button1){
        tableAddRow(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button1){
       tableAddRow(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button1){
        tableAddRow(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button1){
        tableAddRow(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Clone_Clicked()
{
    std::cout<<"CLONE.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button2 ){
        tableCloneRow(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button2){
        tableCloneRow(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button2){
        tableCloneRow(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button2){
       tableCloneRow(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button2){
        tableCloneRow(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button2){
        tableCloneRow(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Del_Clicked()
{
    std::cout<<"DEL.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button3 ){
        tableDelRow(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button3){
        tableDelRow(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button3){
        tableDelRow(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button3){
        tableDelRow(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button3){
        tableDelRow(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button3){
        tableDelRow(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Up_Clicked()
{
    std::cout<<"UP.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button4 ){
        tableUpSel(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button4){
        tableUpSel(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button4){
        tableUpSel(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button4){
       tableUpSel(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button4){
        tableUpSel(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button4){
        tableUpSel(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Down_Clicked()
{
    std::cout<<"DOWN.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button5 ){
        tableDownSel(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button5){
        tableDownSel(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button5){
        tableDownSel(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button5){
       tableDownSel(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button5){
        tableDownSel(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button5){
        tableDownSel(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Top_Clicked()
{
    std::cout<<"TOP.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button6 ){
        tableTopSel(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button6){
        tableTopSel(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button6){
        tableTopSel(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button6){
       tableTopSel(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button6){
        tableTopSel(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button6){
        tableTopSel(ui->at_tableWidget2);
    }
    */
}

void MainWindow::Bottom_Clicked()
{
    std::cout<<"BOTTOM.."<<std::endl;
    QWidget *sender = (QWidget *) QObject::sender();
    if(sender == ui->mt_navTable1_button7 ){
        tableBotSel(ui->mt_tableView1);
    }
    /*
    else if(sender == ui->mt_navTable2_button7){
        tableBotSel(ui->mt_tableWidget2);
    }
    else if(sender == ui->ft_navTable1_button7){
        tableBotSel(ui->ft_tableWidget1);
    }
    else if(sender == ui->ft_navTable2_button7){
       tableBotSel(ui->ft_tableWidget2);
    }
    else if(sender == ui->at_navTable1_button7){
        tableBotSel(ui->at_tableWidget1);
    }
    else if(sender == ui->at_navTable2_button7){
        tableBotSel(ui->at_tableWidget2);
    }
    */
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
    if(rowToClone !=-1)
    {
       ModuleTableModel* m = static_cast<ModuleTableModel*>(table->model());
       m->cloneRow(rowToClone);
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
        std::cout<<"selected: mm "<<rowSelected_<<std::endl;

        ModuleTableModel* m = static_cast<ModuleTableModel*>(ui->mt_tableView1->model());
        RowData* rd = m->getDatainRow(rowSelected_);

        qreal px_ =rd->getData(2).toDouble();
        qreal py_ =rd->getData(3).toDouble();
        qreal w_  =rd->getData(4).toDouble();
        qreal h_  =rd->getData(5).toDouble();

        /* slice image */
        QPixmap pieceImage =pixmapOpened.copy(px_, py_, w_, h_);
        editWindow->getModuleList()->clear();

        QListWidgetItem* item = new QListWidgetItem("ID-"+rd->getData(1));
        item->setIcon(QIcon(pieceImage));
        editWindow->getModuleList()->insertItem(0,item);
        /* end slice image */

        /*
        editWindow->imageLabel->getRectSelectItem()->setPos(px_,py_);

        QRectF rect_ = editWindow->imageLabel->getRectSelectItem()->rect();
        rect_.setHeight(h_);
        rect_.setWidth(w_);
        editWindow->imageLabel->getRectSelectItem()->setRect(rect_);
        */

        QRectF rect_ = editWindow->imageLabel->getRectSelectItem()->rect();
        rect_.setHeight(h_);
        rect_.setWidth(w_);
        editWindow->imageLabel->getRectSelectItem()->setRect(rect_);


       // QPoint delta = editWindow->imageLabel->mapToScene(rect_.x()+1000,rect_.y()+1000);
        px_=px_-rect_.x()+1000;
        py_=py_-rect_.y()+1000;
        editWindow->imageLabel->getRectSelectItem()->setPos(px_,py_);


    }
}

void MainWindow::UpdateDataCell(const QModelIndex & indexA, const QModelIndex & indexB)
{
     //ui->tableView->model()->setData(ui->tableView->model()->index(fila ,col + 1),2.0*valor1);
    //std::cout<<"data changed...........: "<<std::endl;
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

   // QPoint delta = editWindow->imageLabel->mapToScene(rect_.x()+1000,rect_.y()+1000);
    px_=px_-rect_.x()+1000;
    py_=py_-rect_.y()+1000;
    editWindow->imageLabel->getRectSelectItem()->setPos(px_,py_);
}
