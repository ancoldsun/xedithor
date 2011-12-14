
#include <QtGui>
#include <QPainter>
#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include "rectselectionitem.h"

#include <iostream>


RectSelectionItem::RectSelectionItem(QGraphicsItem* parent, QGraphicsScene* scene)
    :QGraphicsRectItem(parent,scene)
{

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptHoverEvents ( true);
}

void RectSelectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //painter->drawLine(line);

    QGraphicsRectItem::paint(painter,option,widget);

}

void RectSelectionItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout<<"rect press event"<<std::endl;

    QGraphicsItem::mousePressEvent(event);
}

void RectSelectionItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    switch(cursor_type)
    {
        case PosCursor::TOP_LEFT :
            {
                // top
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setY(y);
                // left
                qreal x = event->pos().x();
                rect_.setX(x);

                setRect(rect_);
            }
            break;
        case PosCursor::TOP :
            {
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setY(y);
                setRect(rect_);
            }
            break;
        case PosCursor::TOP_RIGHT :
            {
                // top
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setY(y);
                // right
                qreal x = event->pos().x();
                rect_.setWidth(event->pos().x() - rect_.x());

                setRect(rect_);
            }
            break;
        case PosCursor::LEFT_SIDE :
            {
                qreal x = event->pos().x();
                QRectF rect_ = this->rect();
                rect_.setX(x);
                setRect(rect_);
            }
            break;
        case PosCursor::RIGHT_SIDE :
            {
                qreal x = event->pos().x();
                QRectF rect_ = this->rect();
                rect_.setWidth(event->pos().x() - rect_.x());
                setRect(rect_);
            }
            break;
        case PosCursor::BOTTOM_LEFT :
            {
                // bottom
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setHeight(event->pos().y() - rect_.y());
                // left
                qreal x = event->pos().x();
                rect_.setX(x);

                setRect(rect_);
            }
            break;
        case PosCursor::BOTTOM :
            {
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setHeight(event->pos().y() - rect_.y());
                setRect(rect_);
            }
            break;
        case PosCursor::BOTTOM_RIGHT :
            {
                // bottom
                qreal y = event->pos().y();
                QRectF rect_ = this->rect();
                rect_.setHeight(event->pos().y() - rect_.y());
                // left
                qreal x = event->pos().x();
                rect_.setWidth(event->pos().x() - rect_.x());

                setRect(rect_);
            }
            break;
        default:
            break;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void RectSelectionItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    //std::cout<<"~~~~~~~~~~~ hover...."<<std::endl;
   // std::cout<<"---- x: "<<rect().x()<<std::endl;
   // std::cout<<"---- y: "<<rect().y()<<std::endl;
   // std::cout<<"---- x pos: "<<pos().x()<<std::endl;
   // std::cout<<"---- y pos: "<<pos().y()<<std::endl;

    QPointF mpointF= event->pos();

    setFlag(QGraphicsItem::ItemIsMovable, false);
    int adjust = 5;

    cursor_type = PosCursor::NONE;
    if(mpointF.x()>this->rect().x()-adjust && mpointF.x()<this->rect().x()+adjust)
    {
        std::cout<<"left area"<<std::endl;
        if(mpointF.y()>this->rect().y()-adjust && mpointF.y()<this->rect().y()+adjust)
        {
            std::cout<<"TOP LEFT"<<std::endl;
            setCursor(Qt::SizeFDiagCursor);
            cursor_type = PosCursor::TOP_LEFT;
        }
        else if(mpointF.y()>this->rect().y()+rect().height()-adjust && mpointF.y()<this->rect().y()+rect().height()+adjust)
        {
            std::cout<<"BOTTOM LEFT"<<std::endl;
            setCursor(Qt::SizeBDiagCursor);
            cursor_type = PosCursor::BOTTOM_LEFT;
        }
        else
        {
            std::cout<<"SIDE LEFT"<<std::endl;
            setCursor(Qt::SizeHorCursor);
            cursor_type = PosCursor::LEFT_SIDE;
        }
    }
    else if(mpointF.x()>this->rect().x()+adjust && mpointF.x()<this->rect().x()+rect().width()-adjust)
    {
        std::cout<<"center area"<<std::endl;
        if(mpointF.y()>this->rect().y()-adjust && mpointF.y()<this->rect().y()+adjust)
        {
            std::cout<<"TOP"<<std::endl;
            setCursor(Qt::SizeVerCursor);
            cursor_type = PosCursor::TOP;

        }
        else if(mpointF.y()>this->rect().y()+adjust && mpointF.y()<this->rect().y()+rect().height()-adjust)
        {
            std::cout<<"CENTER"<<std::endl;
            setFlag(QGraphicsItem::ItemIsMovable, true);
            setCursor(Qt::CrossCursor);
            cursor_type = PosCursor::CENTER;
        }
        else
        {
            std::cout<<"BOTTOM"<<std::endl;
            setCursor(Qt::SizeVerCursor);
            cursor_type = PosCursor::BOTTOM;
        }
    }
    else if(mpointF.x()>this->rect().x()+rect().width()-adjust && mpointF.x()<this->rect().x()+rect().width()+adjust)
    {
        std::cout<<"right area"<<std::endl;
        if(mpointF.y()>this->rect().y()-adjust && mpointF.y()<this->rect().y()+adjust)
        {
            std::cout<<"TOP RIGHT"<<std::endl;
            setCursor(Qt::SizeBDiagCursor);
            cursor_type = PosCursor::TOP_RIGHT;
        }
        else if(mpointF.y()>this->rect().y()+rect().height()-adjust && mpointF.y()<this->rect().y()+rect().height()+adjust)
        {
            std::cout<<"BOTTOM RIGHT"<<std::endl;
            setCursor(Qt::SizeFDiagCursor);
            cursor_type = PosCursor::BOTTOM_RIGHT;
        }
        else
        {
            std::cout<<"SIDE RIGHT"<<std::endl;
            setCursor(Qt::SizeHorCursor);
            cursor_type = PosCursor::RIGHT_SIDE;
        }
    }
    else
    {
        std::cout<<"NOPE area.............."<<std::endl;
    }
}

void RectSelectionItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout<<"rect release event"<<std::endl;
    QGraphicsItem::mouseReleaseEvent(event);

}

QRectF RectSelectionItem::boundingRect() const
{
   qreal adjust = 0;
   return QRectF( this->rect().x()-adjust,this->rect().y()-adjust,
                  this->rect().width()+2*adjust,this->rect().height()+2*adjust);
}

QPainterPath RectSelectionItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void RectSelectionItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout<<"dragMoveEvent dragMoveEvent.............."<<std::endl;
}
