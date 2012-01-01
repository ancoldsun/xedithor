// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
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
