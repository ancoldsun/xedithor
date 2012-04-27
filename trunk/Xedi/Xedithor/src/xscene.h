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
