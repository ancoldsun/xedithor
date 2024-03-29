
#include <QtGui>

#include "editwindow.h"
#include "ui_editwindow.h"
#include "globalconstant.h"
#include "uidmanager.h"


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
    zoomInAct = new QAction(QIcon(":/images/Selection.png"),tr("&Select.."), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("ZoomIn.."));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(ZoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/pan.png"),tr("&Pan.."), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("ZoomOut.."));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(ZoomOut()));

    windowEditToolBar = new QToolBar(this);
    windowEditToolBar->addAction(zoomInAct);
    windowEditToolBar->addAction(zoomOutAct);
    // fps slider
    QSlider* slider =new QSlider((Qt::Horizontal));
    slider->setFixedWidth(100);
    slider->setTickInterval(99);
    slider->setRange(1,100);
    slider->setValue(default_fps);
    windowEditToolBar->addWidget(slider);
    // fps label
    m_FpsLabel =new QLabel(string_fps+QString::number(default_fps),this);
    windowEditToolBar->addWidget(m_FpsLabel);

    this->addToolBar(windowEditToolBar);
    scaleFactor=1.0f;

    mouseInfoLabel = new QLabel("0,0");
    this->statusBar()->addWidget(mouseInfoLabel);
    imageLabel->setLabelMouse(mouseInfoLabel);

    /* list module/frame  */
    modulesList = new ModulesList(ITEM_PIXMAP::Max_H);
    modulesList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //modulesList always follow the parent (this)
    ui->dockWidgetContents->layout()->addWidget(modulesList);

    modulesList->setViewMode(QListView::ListMode);
    modulesList->setFlow(QListView::TopToBottom);
    modulesList->setSpacing(8);
    modulesList->setLayoutMode(QListView::Batched);

    modulesList->setAutoScroll(true);

    //image list connect
    connect(modulesList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(FrameDoubleClicked(QModelIndex)));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setTimerInterval(int)));
}

void EditWindow::setTimerInterval(int value)
{
    this->imageLabel->setTimerInterval(value);
    QString sFps=string_fps+QString::number(value);
    m_FpsLabel->setText(sFps);
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
    modulesList = new ModulesList(ITEM_PIXMAP::Max_H);
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
    int imgClicked_ = index.row();

    if(m_modeView == TabView::FRAME || m_modeView == TabView::ANIM) {
        QPixmap pixmap = modulesList->item(imgClicked_)->icon().pixmap(ITEM_PIXMAP::Max_W,ITEM_PIXMAP::Max_H);
        QString moduleIDStr = modulesList->item(imgClicked_)->text();
        QPixmap copyPixmap = pixmap.copy();
        int genId_;
        if(m_modeView == TabView::FRAME)
        {
            genId_ = this->imageLabel->AddPixmapItem(&copyPixmap);
        }
        else if(m_modeView == TabView::ANIM)
        {
            int _idPixmap = UID::Instance().getLastUID(UIDType::ANIM_DESC);
            genId_ = this->imageLabel->AddPixmapItem(&copyPixmap,false,_idPixmap,0,0);
        }

        MFATableModel* m = static_cast<MFATableModel*>(this->imageLabel->m_table->model());
        if(m->rowCount()<1){
            m->insertRow(0);

            MFATableModel* sub_model = m->getModel(0);
            sub_model->insertRow(0);
            /* set data */
            RowData* rd = sub_model->getDatainRow(0);
            rd->setData(0,QString::number(genId_));
            rd->setData(1,moduleIDStr);
            /* end set data */
            sub_model->refresh();
            /* update module frame count */
            int mf_count = m->getDatainRow(0)->getData(2).toInt();
            m->getDatainRow(0)->setData(2,QString::number(mf_count+1));

            this->imageLabel->m_table_bottom->setModel(sub_model);
        } else
        {
            int frameRowSelected = imageLabel->m_table->currentIndex().row();
            if(frameRowSelected == -1){
                frameRowSelected = 0;
            }

            MFATableModel* sub_model = m->getModel(frameRowSelected);
            if(sub_model->rowCount()<1)
            {
                sub_model->insertRow(0);

                /* set data */
                RowData* rd = sub_model->getDatainRow(0);
                rd->setData(0,QString::number(genId_));
                rd->setData(1,moduleIDStr);
                /* end set data */
                sub_model->refresh();

                /* update module frame count */
                int mf_count = m->getDatainRow(frameRowSelected)->getData(2).toInt();
                m->getDatainRow(frameRowSelected)->setData(2,QString::number(mf_count+1));
            }
            else
            {
                int frameModuleRowSelected = sub_model->rowCount();
                sub_model->insertRow(frameModuleRowSelected);
                /* set data */
                RowData* rd = sub_model->getDatainRow(frameModuleRowSelected);
                rd->setData(0,QString::number(genId_));
                rd->setData(1,moduleIDStr);
                /* end set data */
                sub_model->refresh();

                /* update module frame count */
                int mf_count = m->getDatainRow(frameRowSelected)->getData(2).toInt();
                m->getDatainRow(frameRowSelected)->setData(2,QString::number(mf_count+1));
            }
        }
        m->refresh();
    }  // -- end TabView::FRAME
}

void EditWindow::setupViewModule()
{
    m_modeView= TabView::MODULE;
    this->imageLabel->setupGraphViewModule();
}

void EditWindow::setupViewFrame()
{
    m_modeView= TabView::FRAME;
    this->imageLabel->setupGraphViewFrame();
}

void EditWindow::setupViewAnim()
{
    m_modeView= TabView::ANIM;

    //imageLabel->setupGraphViewAnim();
}

void EditWindow::createAnimation()
{
    MFATableModel* _model      =static_cast<MFATableModel*>(this->imageLabel->m_table_bottom->model());

    QList<QPixmap> listPixmap;
    QList<QPoint> listPos;
    QList<int> listTimeShown;
    for(int i=0;i<_model->rowCount();i++)
    {
        RowData* rd = _model->getDatainRow(i);

        QString moduleID_ = rd->getData(1);
        int _posx         = rd->getData(2).toInt();
        int _posy         = rd->getData(3).toInt();
        int timeShown     = rd->getData(4).toInt();

        QListWidgetItem* item = modulesList->getItemByText(moduleID_);
        QPixmap pixmap;
        if(item!=NULL)
        {
            pixmap = item->icon().pixmap(ITEM_PIXMAP::Max_W,ITEM_PIXMAP::Max_H);
        }
        else
        {
            pixmap = QPixmap::fromImage(QImage(":/images/invalidF.png"));
        }
        QPixmap copyPixmap = pixmap.copy();

        listPixmap.push_back(copyPixmap);

        QPoint _pos(_posx,_posy);
        listPos.push_back(_pos);
        listTimeShown.push_back(timeShown);

    }
    imageLabel->createAnimation(listPixmap,listPos,listTimeShown);
}
