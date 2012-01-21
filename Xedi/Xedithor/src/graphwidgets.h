// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
#ifndef GRAPHWIDGETS_H
#define GRAPHWIDGETS_H

#include <QtGui/QGraphicsView>
#include <qtableview.h>
#include <QTimerEvent>
#include <QTimer>

#include "mfatablemodel.h"

#include "xscene.h"
#include "rectselectionitem.h"
#include "hlinegraphicsitem.h"
#include "rowdata.h"
#include "animatedPixmapItem.h"

QT_BEGIN_NAMESPACE
    class QLabel;
QT_END_NAMESPACE

namespace ModeView
{
    const int EDIT_MODE = 0;
    const int DRAG_MODE = 1;
};



class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RowData* rowDataSelected;
    QTableView* m_table;
    QTableView* m_table_bottom;

    int posMouseX;
    int posMouseY;
    void setImageGraphicsItem(QPixmap* pxmap);
    QPixmap* getImageGraphicsItem();
    void setModeView(const int mode);
    GraphWidget(QWidget *parent = 0);
    QGraphicsRectItem* getRectSelectItem()
    {
        return rectSelect;
    }
    void setupGraphViewModule();
    void setupGraphViewFrame();
    void setupGraphViewAnim();
    int AddPixmapItem(QPixmap* pxmap);
    int AddPixmapItem(QPixmap* pxmap,bool isGenerateID,int idFrameModule,int posx_,int posy_);
    void clearGraphPixmapItem();
    void setSelectedPixmapItem(int idSelected);
    void DeletePixmapItem(int idDeleted);
    QImage exportToImage();
    void createAnimation(QList<QPixmap>&list,QList<QPoint>&listPos);
    inline void clearAnimation() {
        if(m_animatedItem!=NULL)
        {
            delete m_animatedItem;
            m_animatedItem=NULL;
        }
    }

    inline void setTimerInterval(int value){
        this->m_timer->setInterval(value*10);
    }


public slots:
    void setLabelMouse(QLabel* labelmouseinv);
    void timerHit();

protected:
    //Holds the current centerpoint for the view, used for panning and zooming
    QPointF CurrentCenterPoint;

    //From panning the view
    QPoint LastPanPoint;
    QPoint FirstRectPoint;
    QPoint LastRectPoint;

    //Set the current centerpoint in the
    void SetCenter(const QPointF& centerPoint);
    QPointF GetCenter() { return CurrentCenterPoint; }

    //Take over the interaction
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);

    virtual void drawForeground(QPainter* painter,const QRectF &rect);
    virtual void timerEvent( QTimerEvent * );


private:
    int timerId;
    int modeView;
    int m_tabView;
    QPixmap* pixmap;
    QLabel* labelmouse;
    QRect* rectPointer;
    QGraphicsPixmapItem* pixmapGraphicsItem;
    RectSelectionItem* rectSelect;
    QTimer *m_timer;

    HLineGraphicsItem* lineH;
    XScene *m_scene;
    AnimatedPixmapItem* m_animatedItem;

};


#endif // GRAPHWIDGETS_H
