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

#ifndef ANIMATEDPIXMAPITEM_H
#define ANIMATEDPIXMAPITEM_H


#include <QGraphicsItem>
#include <QElapsedTimer>

class AnimatedPixmapItem : public QGraphicsItem
{
public:
    AnimatedPixmapItem(const QList<QPixmap>& animation,const QList<QPoint>& listPos,const QList<int>&listTimeShown, QGraphicsScene *scene = 0);

    void setFrame(int frame);
    inline int frame() const  {
        return currentFrame;
    }
    inline int frameCount() const {
        return frames.size();
    }
    inline QPixmap image(int frame) const {
        return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap;
    }
    inline void setVelocity(qreal xvel, qreal yvel) {
        vx = xvel; vy = yvel;
    }
    inline qreal xVelocity() const {
        return vx;
    }
    inline qreal yVelocity() const {
        return vy;
    }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
    void nextFrame();

private:
    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
        QPoint position;
        int timeShow;
    };

    int currentFrame;
    QList<Frame> frames;
    qreal vx, vy;
    QElapsedTimer m_frameTimeElapsed;
};

#endif // ANIMATEDPIXMAPITEM_H
