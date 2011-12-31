// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
#ifndef XSCENE_H
#define XSCENE_H

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

class QGraphicsSceneMouseEvent;
class QGraphicsSceneDragDropEvent;

class XScene : public QGraphicsScene
{
        Q_OBJECT

public:
        XScene(QObject* parent=0);

public:
        void dragEnterEvent( QGraphicsSceneDragDropEvent * );
        void dragMoveEvent( QGraphicsSceneDragDropEvent * );
        void dropEvent( QGraphicsSceneDragDropEvent * );
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};

#endif // XSCENE_H
