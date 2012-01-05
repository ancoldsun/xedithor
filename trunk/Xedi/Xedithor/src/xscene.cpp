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

}


void XScene::dropEvent( QGraphicsSceneDragDropEvent * ev )
{

}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
}

void XScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);

}




