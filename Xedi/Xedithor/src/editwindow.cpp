
#include <QtGui>

#include "editwindow.h"
#include "ui_editwindow.h"


EditWindow::EditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    //init
    imageLabel = new GraphWidget;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);

    this->setCentralWidget(imageLabel);

    //create Actions
    zoomInAct = new QAction(QIcon(":/images/Selection.png"),tr("&ZoomIn"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("ZoomIn.."));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(ZoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/pan.png"),tr("&ZoomOut..."), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("ZoomOut.."));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(ZoomOut()));

    windowEditToolBar = new QToolBar(this);
    windowEditToolBar->addAction(zoomInAct);
    windowEditToolBar->addAction(zoomOutAct);
    this->addToolBar(windowEditToolBar);
    scaleFactor=1.0f;

    mouseInfoLabel = new QLabel("0,0");
    this->statusBar()->addWidget(mouseInfoLabel);
    imageLabel->setLabelMouse(mouseInfoLabel);

    /* list module/frame  */
    modulesList = new ModulesList(500);
    modulesList->setFixedWidth(300);
    modulesList->setFixedHeight(600);
    modulesList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    modulesList->setParent(ui->dockWidgetContents);

    modulesList->setViewMode(QListView::ListMode);
    modulesList->setFlow(QListView::TopToBottom);
    modulesList->setSpacing(8);
    modulesList->setLayoutMode(QListView::Batched);

    modulesList->setAutoScroll(true);

    //image list connect
    connect(modulesList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(FrameDoubleClicked(QModelIndex)));

}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::ZoomIn()
{
    imageLabel->setModeView(ModeView::EDIT_MODE);
}

void EditWindow::ZoomOut()
{
   imageLabel->setModeView(ModeView::DRAG_MODE);
}


void EditWindow::scaleImage(double factor)
{
    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 5.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void EditWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void EditWindow::setModuleList_Module()
{
    modulesList = new ModulesList(500);
    modulesList->setFixedWidth(510);
    modulesList->setFixedHeight(800);
    modulesList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    modulesList->setParent(ui->dockWidgetContents);

    modulesList->setViewMode(QListView::ListMode);
    modulesList->setFlow(QListView::TopToBottom);
    modulesList->setSpacing(8);
    modulesList->setLayoutMode(QListView::Batched);
}

void EditWindow::setModuleList_Frame()
{
    modulesList->setViewMode(QListView::ListMode);
    modulesList->setFlow(QListView::TopToBottom);
    modulesList->setSpacing(12);
    modulesList->setLayoutMode(QListView::Batched);
}

void EditWindow::setModuleList_Anim()
{

}

void EditWindow::FrameDoubleClicked(const QModelIndex& index)
{
    std::cout<<"image index: "<<index.row()<<std::endl;

    int imgClicked_ = index.row();

    QPixmap pixmap = modulesList->item(imgClicked_)->icon().pixmap(500,500);
    QString moduleIDStr = modulesList->item(imgClicked_)->text();
    QPixmap copyPixmap = pixmap.copy();
    int genId_ = this->imageLabel->AddPixmapItem(&copyPixmap);
    //QString genIdStr = QString::number(genId_)
    ModuleTableModel* m = static_cast<ModuleTableModel*>(this->imageLabel->m_table->model());
    if(m->rowCount()<1){
        m->insertRow(0);
        m->refresh();

        ModuleTableModel* sub_model = m->getModel(0);
        sub_model->insertRow(0);
        /* set data */
        RowData* rd = sub_model->getDatainRow(0);
        rd->setData(0,QString::number(genId_));
        rd->setData(1,moduleIDStr);
        /* end set data */
        sub_model->refresh();
        this->imageLabel->m_table_bottom->setModel(sub_model);
    } else
    {
        int frameRowSelected = imageLabel->m_table->currentIndex().row();
        if(frameRowSelected == -1){
            frameRowSelected = 0;
        }

        ModuleTableModel* sub_model = m->getModel(frameRowSelected);
        if(sub_model->rowCount()<1){
            sub_model->insertRow(0);

            /* set data */
            RowData* rd = sub_model->getDatainRow(0);
            rd->setData(0,QString::number(genId_));
            rd->setData(1,moduleIDStr);
            /* end set data */
            sub_model->refresh();


        }
        else {
            int frameModuleRowSelected = imageLabel->m_table_bottom->currentIndex().row();
            if(frameModuleRowSelected == -1){
                frameModuleRowSelected = 0;
            }
            sub_model->insertRow(frameModuleRowSelected);
            /* set data */
            RowData* rd = sub_model->getDatainRow(0);
            rd->setData(0,QString::number(genId_));
            rd->setData(1,moduleIDStr);
            /* end set data */
            sub_model->refresh();
            sub_model->refresh();
        }
    }
}
