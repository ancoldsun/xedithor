// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
#ifndef MODULETABLEMODEL_H
#define MODULETABLEMODEL_H


#include <QAbstractTableModel>
#include <QString>
#include <qlist.h>
#include <QStringList>
#include <QTimer>
#include <QColor>

#include "rowdata.h"

class ModuleTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModuleTableModel(QObject *parent,int row,int col,RowDataHandler* rowHandler);
    ~ModuleTableModel();
    void setupTable();
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;
    bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool cloneRow(int row);
    bool swapRow(int row1,int row2);
    RowData* getDatainRow(int iRow);
    inline void setHasModel(bool isHasModel){
        m_hasModel=isHasModel;
    }

    inline void setSubModelRowHandler(RowDataHandler* _row_handler) {
        m_subHandler = _row_handler;
    }

    ModuleTableModel* getModel(int rowN);
    void copyContent(ModuleTableModel* otherModel);

    void clearData();
    void refresh();
    inline void AddEditableColumn(int colEditable){
        m_editableColumn.push_back(colEditable);
    }

private:
    //QString m_gridData[ROWS][COLS];  //holds text entered into QTableView
    QList<RowData*>  m_gridData2;
    int numberRow,numberCol;
    QStringList m_Headers;
    RowDataHandler* m_handler;
    RowDataHandler* m_subHandler;
    QList<ModuleTableModel*> m_listModel;
    QList<int> m_editableColumn;
    bool m_hasModel;

    //QTimer *timer;


signals:
    void editCompleted(const QString &);
private slots:
    void timerHit();
};

#endif // MODULETABLEMODEL_H
