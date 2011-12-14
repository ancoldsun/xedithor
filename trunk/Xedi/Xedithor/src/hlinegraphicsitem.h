/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/

#ifndef HLINEGRAPHICSITEM_H
#define HLINEGRAPHICSITEM_H


#include <QGraphicsItem>

class GraphWidget;

class HLineGraphicsItem : public QGraphicsItem
{
public:
   // HLineGraphicsItem(QPointF src,QPointF dst);
    void setSourcePoint(QPointF& pointSrc);
    void setDestPoint(QPointF& pointDest);
protected:
    /*
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};
#endif // HLINEGRAPHICSITEM_H
