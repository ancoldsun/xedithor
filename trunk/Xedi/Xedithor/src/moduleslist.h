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

#ifndef MODULESLIST_H
#define MODULESLIST_H

#include <QListWidget>


class ModulesList : public QListWidget
{
    Q_OBJECT

public:
    ModulesList(int pieceSize, QWidget *parent = 0);
    void addPiece(QPixmap pixmap, QPoint location,QString str="");
    QListWidgetItem* getItemByText(QString str);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
private:
    int m_PieceSize;
};

#endif // MODULESLIST_H
