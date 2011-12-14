

#include <QPainter>
#include <math.h>

#include "hlinegraphicsitem.h"

#include <iostream>

QRectF HLineGraphicsItem::boundingRect() const
{
    qreal penWidth = 3;
    qreal extra = (penWidth ) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void HLineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF line(sourcePoint, destPoint);
    painter->setPen(QPen(Qt::red, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

void HLineGraphicsItem::setSourcePoint(QPointF& pointSrc)
{
    sourcePoint=pointSrc;
}

void HLineGraphicsItem::setDestPoint(QPointF& pointDest)
{
    destPoint=pointDest;
}

/*
void HLineGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout<<"rect press event"<<std::endl;
}

void HLineGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout<<"rect release event"<<std::endl;
}
*/



