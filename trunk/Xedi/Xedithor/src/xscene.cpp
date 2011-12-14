#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSceneDragDropEvent>
#include <QtGui/QGraphicsSceneMouseEvent>

#include <iostream>

#include "xscene.h"


XScene::XScene(QObject *parent):QGraphicsScene(parent)
{

}

void XScene::dragEnterEvent( QGraphicsSceneDragDropEvent * ev )
{

}


void XScene::dragMoveEvent( QGraphicsSceneDragDropEvent * ev )
{
    std::cout<<"XScene dragMoveEvent("<<std::endl;
}


void XScene::dropEvent( QGraphicsSceneDragDropEvent * ev )
{

}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cout<<"XScene mousePressEvent("<<std::endl;
    QGraphicsScene::mousePressEvent(event);
}

void XScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cout<<"XScene mouseMoveEvent"<<std::endl;
    QGraphicsScene::mouseMoveEvent(event);
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cout<<"XScene mouseReleaseEvent("<<std::endl;
    QGraphicsScene::mouseReleaseEvent(event);

}




