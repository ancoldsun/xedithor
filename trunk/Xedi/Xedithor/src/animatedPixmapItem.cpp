#include "animatedPixmapItem.h"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>
#include <QGraphicsScene>
#include <iostream>

AnimatedPixmapItem::AnimatedPixmapItem(const QList<QPixmap> &animation,
                                       const QList<QPoint> &listPos,
                                       QGraphicsScene *scene)
    : QGraphicsItem(0), currentFrame(0), vx(0), vy(0)
{
    for (int i = 0; i < animation.size(); ++i) {
        QPixmap pixmap = animation.at(i);
        Frame frame;
        frame.pixmap = pixmap;
        frame.shape = QPainterPath();
        frame.boundingRect = pixmap.rect();
        frame.position = listPos.at(i);
        frames << frame;
    }

    scene->addItem(this);
    std::cout<<"constructor: "<<currentFrame<<std::endl;
}

void AnimatedPixmapItem::setFrame(int frame)
{
    if (!frames.isEmpty()) {
        prepareGeometryChange();
        currentFrame = frame % frames.size();
    }
    std::cout<<"setFrame: "<<currentFrame<<std::endl;
}

void AnimatedPixmapItem::nextFrame()
{
    if(currentFrame<frames.count()-1)
    {
             currentFrame++;
    }
    else
    {
            currentFrame=0;
    }
}

void AnimatedPixmapItem::advance(int phase)
{
    if (phase == 1)
        moveBy(vx, vy);
}

QRectF AnimatedPixmapItem::boundingRect() const
{
    return frames.at(currentFrame).boundingRect;
}

QPainterPath AnimatedPixmapItem::shape() const
{
    const Frame &f = frames.at(currentFrame);
    if (f.shape.isEmpty()) {
        QPainterPath path;
        path.addRegion(f.pixmap.createHeuristicMask());
        const_cast<Frame &>(f).shape = path;
    }
    return f.shape;
}

void AnimatedPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
                               QWidget * /*widget*/)
{
    QPoint posFrame = frames.at(currentFrame).position;
    painter->drawPixmap(posFrame.x(), posFrame.y(), frames.at(currentFrame).pixmap);
    std::cout<<"Frame: "<<currentFrame<<std::endl;
}

