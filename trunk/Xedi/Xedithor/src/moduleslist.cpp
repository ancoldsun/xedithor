#include <QtGui>

#include "moduleslist.h"

ModulesList::ModulesList(int pieceSize, QWidget *parent)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(10);

    //setAcceptDrops(true);
    //setDropIndicatorShown(true);
}

void ModulesList::dragEnterEvent(QDragEnterEvent *event)
{
    /*
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
    */
}

void ModulesList::dragMoveEvent(QDragMoveEvent *event)
{
    /*
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
    */
}

void ModulesList::dropEvent(QDropEvent *event)
{
    /*
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        addPiece(pixmap, location);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
    */
}

void ModulesList::addPiece(QPixmap pixmap, QPoint location,QString str)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setText(str);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
}

void ModulesList::startDrag(Qt::DropActions /*supportedActions*/)
{
    /*
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
    */
}

QListWidgetItem* ModulesList::getItemByText(QString str)
{
    for(int i=0;i<this->count();i++){
        QListWidgetItem* item_ = item(i);
        if(!(item_->text().compare(str))){
            return item_;
        }
    }
    return NULL;
}

