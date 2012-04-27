// Xedithor : 2D sprite editor
// Copyright [2011] Edi Ermawan <edi.ermawan@gmail.Com>

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
