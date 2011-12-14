/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/
#ifndef RECTSELECTIONITEM_H
#define RECTSELECTIONITEM_H


#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


namespace PosCursor
{
    const int TOP_LEFT       = 0;
    const int TOP            = 1;
    const int TOP_RIGHT      = 2;
    const int LEFT_SIDE      = 3;
    const int RIGHT_SIDE     = 4;
    const int BOTTOM_LEFT    = 5;
    const int BOTTOM         = 6;
    const int BOTTOM_RIGHT   = 7;
    const int CENTER         = 8;
    const int NONE           = 9;
};

class RectSelectionItem : public QGraphicsRectItem
{

public:
    RectSelectionItem(QGraphicsItem* parent=0, QGraphicsScene* scene=0);
protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    int cursor_type;


};

#endif // RECTSELECTIONITEM_H
