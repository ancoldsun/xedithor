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
#include "globalconstant.h"

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
    QGraphicsRectItem* getRectSelectItem() {
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
    void addAxis();
    void hideAxis();
    void showAxis();

    inline void clearAnimation() {
        if(m_animatedItem!=NULL)
        {
            delete m_animatedItem;
            m_animatedItem=NULL;
        }
    }

    inline void setTimerInterval(int value){
        std::cout<<" fps: "<<value<<std::endl;
        this->m_timer->setInterval((millisecond/value));
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
    QGraphicsItemGroup* m_AxisGroup;

    HLineGraphicsItem* lineH;
    XScene *m_scene;
    AnimatedPixmapItem* m_animatedItem;

};


#endif // GRAPHWIDGETS_H
