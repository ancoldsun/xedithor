#include <QtGui>
#include <QPainter>
#include <math.h>
#include <QGraphicsPixmapItem>

#include "globalconstant.h"
#include "graphwidgets.h"
#include "rectselectionitem.h"
#include "uidmanager.h"

#include <iostream>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    m_scene = new XScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    posMouseX = 0;
    posMouseY = 0;
    pixmapGraphicsItem=NULL;

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_AxisGroup = new QGraphicsItemGroup();
    addAxis();
    //Set-up the view
    setSceneRect(0, 0, WidthRectView, HeightRectView);
    SetCenter(QPointF(WidthRectView / 2, HeightRectView / 2)); //A modified version of centerOn(), handles special cases
    setCursor(Qt::OpenHandCursor);

    //rect selection
    rectSelect = new RectSelectionItem;
    rectSelect->setRect(WidthRectView / 2,HeightRectView / 2,32.0,32.0);

    QPen pen;
    pen.setBrush(QBrush(Qt::NoBrush));
    pen.setColor(QColor(Qt::red));
    pen.setWidthF(0.7f);
    pen.setStyle(Qt::DashLine);
    rectSelect->setPen(pen);
    rectSelect->setZValue(0.9);
    m_scene->addItem(rectSelect);

    modeView = ModeView::DRAG_MODE;
    m_tabView = TabView::MODULE;

    rowDataSelected = NULL;

    m_table_bottom=NULL;
    m_animatedItem = NULL;

    m_timer =new QTimer(this);
    m_timer->setInterval(millisecond/default_fps);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    m_timer->start(millisecond/default_fps);
}

void GraphWidget::setImageGraphicsItem(QPixmap* pxmap)
{
    delete pixmapGraphicsItem;

    pixmap=pxmap;
    pixmapGraphicsItem= new QGraphicsPixmapItem(*pixmap);
    pixmapGraphicsItem->setPos(WidthRectView / 2 , HeightRectView / 2 );
    this->scene()->addItem(pixmapGraphicsItem);
}

QPixmap* GraphWidget::getImageGraphicsItem()
{
    return &pixmapGraphicsItem->pixmap();
}

void GraphWidget::setLabelMouse(QLabel* labelmouseinv)
{
    labelmouse=labelmouseinv;
}


/*
  * Sets the current centerpoint.  Also updates the scene's center point.
  * Unlike centerOn, which has no way of getting the floating point center
  * back, SetCenter() stores the center point.  It also handles the special
  * sidebar case.  This function will claim the centerPoint to sceneRec ie.
  * the centerPoint must be within the sceneRec.
  */
//Set the current centerpoint in the
void GraphWidget::SetCenter(const QPointF& centerPoint) {
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();

    //Get the scene area
    QRectF sceneBounds = sceneRect();

    double boundX = visibleArea.width() ;
    double boundY = visibleArea.height();
    double boundWidth = sceneBounds.width();
    double boundHeight = sceneBounds.height();

    //The max boundary that the centerPoint can be to
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    if(bounds.contains(centerPoint)) {
        //We are within the bounds
        CurrentCenterPoint = centerPoint;
    } else {
        //We need to clamp or use the center of the screen
        if(visibleArea.contains(sceneBounds)) {
            //Use the center of scene ie. we can see the whole scene
            CurrentCenterPoint = sceneBounds.center();
        } else {

            CurrentCenterPoint = centerPoint;

            //We need to clamp the center. The centerPoint is too large
            if(centerPoint.x() > bounds.x() + bounds.width()) {
                CurrentCenterPoint.setX(bounds.x() + bounds.width());
            } else if(centerPoint.x() < bounds.x()) {
                CurrentCenterPoint.setX(bounds.x());
            }

            if(centerPoint.y() > bounds.y() + bounds.height()) {
                CurrentCenterPoint.setY(bounds.y() + bounds.height());
            } else if(centerPoint.y() < bounds.y()) {
                CurrentCenterPoint.setY(bounds.y());
            }

        }
    }

    //Update the scrollbars
    centerOn(CurrentCenterPoint);
}

// Handles when the mouse button is pressed

void GraphWidget::mousePressEvent(QMouseEvent* event)
{
    //For panning the view
    LastPanPoint = event->pos();
    FirstRectPoint= event->pos();
    QGraphicsView::mousePressEvent(event);
}

// Handles when the mouse button is released

void GraphWidget::mouseReleaseEvent(QMouseEvent* event) {
    // setCursor(Qt::OpenHandCursor);
    LastPanPoint = QPoint();

    LastRectPoint= event->pos();
    if(m_tabView == TabView::FRAME) {
        if(m_scene->selectedItems().count()>0) {
            MFATableModel* m2;
            foreach (QGraphicsItem *item, m_scene->selectedItems()) {
                if(item->type()== QGraphicsPixmapItem::Type){

                    int itemPosX = (item->pos().x()-(WidthRectView / 2));
                    int itemPosY = (item->pos().y()-(HeightRectView / 2));

                    int idItem = item->data(0).toInt();

                    m2 =static_cast<MFATableModel*>(m_table_bottom->model());

                    for(int i=0;i<m2->rowCount();i++){
                        RowData* rd = m2->getDatainRow(i);
                        if(rd!=NULL && rd->getData(0).toInt()==idItem){
                            QString sx = QString::number(itemPosX);
                            QString sy = QString::number(itemPosY);
                            rd->setData(2,sx);
                            rd->setData(3,sy);
                        }
                    }

                }
            }
            m2->refresh();
        }
    } // --- if view module

    QGraphicsView::mouseReleaseEvent(event);
}


//Handles the mouse move event

void GraphWidget::mouseMoveEvent(QMouseEvent* event) {
    if(modeView == ModeView::DRAG_MODE && m_scene->selectedItems().count()==0){
        if(!LastPanPoint.isNull()) {
            //Get how much we panned
            QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
            LastPanPoint = event->pos();

            //Update the center ie. do the pan
            SetCenter(GetCenter() + delta);
        }
    }

    posMouseX=event->pos().x();
    posMouseY=event->pos().y();

    LastRectPoint= event->pos();

    QPointF coordMouse = mapToScene(posMouseX,posMouseY);

    QString xyStr = QString::number((coordMouse.x())-(WidthRectView/2));
    xyStr.append(", ");
    xyStr.append(QString::number((coordMouse.y())-(HeightRectView/2)));

    labelmouse->setText(xyStr);
    coordMouse = mapToScene(LastRectPoint.x(),LastRectPoint.y());


    if(m_tabView == TabView::MODULE) {
        MFATableModel* m =static_cast<MFATableModel*>(m_table->model());
        int rowSelected_ = m_table->currentIndex().row();

        if(rowSelected_!=-1)
        {
            RowData* rd = m->getDatainRow(rowSelected_);
            QString sh = QString::number((int)(rectSelect->rect().width()));
            QString sw = QString::number((int)(rectSelect->rect().height()));
            QString sx = QString::number((int)(rectSelect->pos().x()+rectSelect->rect().x()-(WidthRectView / 2)));
            QString sy = QString::number((int)(rectSelect->pos().y()+rectSelect->rect().y()-(HeightRectView / 2)));

            rd->setData(2,sx);
            rd->setData(3,sy);
            rd->setData(4,sh);
            rd->setData(5,sw);

            m->refresh();
       }
    }
    QGraphicsView::mouseMoveEvent(event);
}


/*
  * Zoom the view in and out.
  */
void GraphWidget::wheelEvent(QWheelEvent* event) {

    //Get the position of the mouse before scaling, in scene coords
    QPointF pointBeforeScale(mapToScene(event->pos()));

    //Get the original screen centerpoint
    QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());

    //Scale the view ie. do the zoom
    double scaleFactor = 1.15; //How fast we zoom
    if(event->delta() > 0) {
        //Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        //Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    //Get the position after scaling, in scene coords
    QPointF pointAfterScale(mapToScene(event->pos()));

    //Get the offset of how the screen moved
    QPointF offset = pointBeforeScale - pointAfterScale;

    //Adjust to the new center for correct zooming
    QPointF newCenter = screenCenter + offset;
    SetCenter(newCenter);
}

/*
  * Need to update the center so there is no jolt in the
  * interaction after resizing the widget.
  */
void GraphWidget::resizeEvent(QResizeEvent* event) {
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    SetCenter(visibleArea.center());

    //Call the subclass resize so the scrollbars are updated correctly
    QGraphicsView::resizeEvent(event);
}


void GraphWidget::drawForeground(QPainter* painter,const QRectF &rect)
{

}

void GraphWidget::setModeView(const int mode) {
    modeView = mode;

    switch(modeView)
    {
    case ModeView::DRAG_MODE :  //setCursor(Qt::SizeFDiagCursor);
                                break;
    case ModeView::EDIT_MODE :  setCursor(Qt::CrossCursor);
                                break;
    }
}

void GraphWidget::dragMoveEvent(QDragMoveEvent* event)
{

}

void GraphWidget::setupGraphViewModule()
{
    if(m_animatedItem!=NULL)
    {
        delete m_animatedItem;
        m_animatedItem=NULL;
    }
    clearGraphPixmapItem();

    m_scene->addItem(rectSelect);
    if(pixmapGraphicsItem != NULL)
        m_scene->addItem(pixmapGraphicsItem);
    m_tabView = TabView::MODULE;
}

void GraphWidget::setupGraphViewFrame()
{
    if(m_animatedItem!=NULL)
    {
        delete m_animatedItem;
        m_animatedItem=NULL;
    }

    clearGraphPixmapItem();
    // check whether rectSelect is available or not
    foreach (QGraphicsItem *item, m_scene->items()) {
        if(item == rectSelect){
            m_scene->removeItem(item);
        }
    }

    if(pixmapGraphicsItem != NULL)
       m_scene->removeItem(pixmapGraphicsItem);
    m_tabView = TabView::FRAME;
}

void GraphWidget::setupGraphViewAnim()
{
    clearGraphPixmapItem();
    m_tabView = TabView::ANIM;
}

int GraphWidget::AddPixmapItem(QPixmap* pxmap)
{
    return AddPixmapItem(pxmap,true,0,0,0);
}

int GraphWidget::AddPixmapItem(QPixmap* pxmap,bool isGenerateID,int idFrameModule,int posx_,int posy_)
{
    QGraphicsPixmapItem* itemPixMap= new QGraphicsPixmapItem(*pxmap);
    itemPixMap->setPos(posx_ + WidthRectView / 2 ,posy_ +  HeightRectView / 2 );
    itemPixMap->setFlag(QGraphicsItem::ItemIsSelectable, true);
    itemPixMap->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    itemPixMap->setAcceptHoverEvents ( true);
    itemPixMap->setFlag( QGraphicsItem::ItemIsMovable, true );

    QVariant varI;
    int id_ =0;
    if(isGenerateID){
        id_ = UID::Instance().getLastUID(UIDType::FRAME_DESC);
    } else {
        id_ = idFrameModule;
    }
    varI.setValue(id_);
    itemPixMap->setData(0,varI);
    this->scene()->addItem(itemPixMap);

    return id_;
}

void GraphWidget::clearGraphPixmapItem()
{
    foreach (QGraphicsItem *item, m_scene->items()) {
        if(item->type()== QGraphicsPixmapItem::Type){
            m_scene->removeItem(item);
        }
    }
}


void GraphWidget::setSelectedPixmapItem(int idSelected)
{
    foreach (QGraphicsItem *item, m_scene->items()) {
        if(item->type()== QGraphicsPixmapItem::Type){
            QVariant dat = item->data(0);
            int intDat = dat.toInt();
            if(intDat == idSelected) {
                item->setSelected(true);
            } else {
                item->setSelected(false);
            }
        }
    }
}

void GraphWidget::DeletePixmapItem(int idDeleted)
{
    foreach (QGraphicsItem *item, m_scene->items()) {
        if(item->type()== QGraphicsPixmapItem::Type){
            QVariant dat = item->data(0);
            int intDat = dat.toInt();
            if(intDat == idDeleted) {
                m_scene->removeItem(item);
                break;
            }
        }
    }
}

QImage GraphWidget::exportToImage()
{
    QRect sourceRect;
    //QRect destRect;
    QList<QGraphicsItem *> selectedItems;

    foreach (QGraphicsItem *item, m_scene->items()) {
        if(item->type()== QGraphicsPixmapItem::Type){
                selectedItems.push_back(item);
        }
    }

    foreach(QGraphicsItem *current, selectedItems) {
        sourceRect = sourceRect.unite((current->sceneBoundingRect().toRect()));
    }

    QImage image(sourceRect.width(),sourceRect.height(),QImage::Format_ARGB32);
    image.fill(0);
    QPainter painter(&image);
    m_scene->render(&painter, image.rect(), sourceRect,Qt::IgnoreAspectRatio);

    return image;
}

void GraphWidget::createAnimation(QList<QPixmap>&list,QList<QPoint>&listPos,QList<int>&listTimeShown)
{

    if(m_animatedItem!=NULL)
    {
        delete m_animatedItem;
        m_animatedItem=NULL;
    }
    if(list.count()>0)
    {
        m_animatedItem = new AnimatedPixmapItem(list,listPos,listTimeShown,this->m_scene);
        m_animatedItem->setPos(WidthRectView / 2 ,HeightRectView / 2 );
        m_animatedItem->setFrame( 0 );
    }

}

void GraphWidget::timerEvent( QTimerEvent * )
{
    if(m_animatedItem!=NULL){
        m_animatedItem->nextFrame();
    }
}

void GraphWidget::timerHit()
{
    if(m_animatedItem!=NULL)
    {
        m_animatedItem->nextFrame();
        repaint();
    }
}

void GraphWidget::addAxis()
{
    // X-axis component
    //m_scene->addLine(0,HeightRectView / 2,WidthRectView, HeightRectView / 2);
    QGraphicsLineItem* lineX = new QGraphicsLineItem(0,HeightRectView / 2,WidthRectView, HeightRectView / 2);
    m_AxisGroup->addToGroup(lineX);
    for(int x = 0; x < WidthRectView; x = x + 25) {
        if(x % 100 == 0 ) {
            QString pointString;
            QTextStream stream(&pointString);
            stream << x - WidthRectView/2;
            QGraphicsTextItem* item = new QGraphicsTextItem(pointString);
            item->setPos(x, HeightRectView / 2);
            m_AxisGroup->addToGroup(item);
        }
        QGraphicsRectItem* _rect = new QGraphicsRectItem(x, HeightRectView / 2, 1, 1);
        m_AxisGroup->addToGroup(_rect);
       //m_scene->addRect(x, HeightRectView / 2, 1, 1);
    }
    // Y-axis component
    //m_scene->addLine(WidthRectView / 2,0,WidthRectView / 2, HeightRectView);
    QGraphicsLineItem* lineY = new QGraphicsLineItem(WidthRectView / 2,0,WidthRectView / 2, HeightRectView);
    m_AxisGroup->addToGroup(lineY);
    for(int y = 0; y < HeightRectView; y = y + 25) {
        if(y % 100 == 0 ) {
            QString pointString;
            QTextStream stream(&pointString);
            stream << y - HeightRectView/2;
            QGraphicsTextItem* item = new QGraphicsTextItem(pointString);
            item->setPos(WidthRectView / 2,y);
            m_AxisGroup->addToGroup(item);
        }
        //m_scene->addRect(WidthRectView / 2, y, 1, 1);
        QGraphicsRectItem* _rect = new QGraphicsRectItem(WidthRectView / 2, y, 1, 1);
        m_AxisGroup->addToGroup(_rect);
    }
    m_scene->addItem(m_AxisGroup);
}

void GraphWidget::hideAxis()
{
    m_scene->removeItem(m_AxisGroup);
}
void GraphWidget::showAxis()
{
    m_scene->addItem(m_AxisGroup);
}



