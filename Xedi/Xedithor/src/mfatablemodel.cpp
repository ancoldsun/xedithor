
#include "mfatablemodel.h"

int RowData::mLast_ID_Module=0;

MFATableModel::MFATableModel(QObject *parent,int row,int col,RowDataHandler* rowHandler)
    :QAbstractTableModel(parent)
{
    numberRow=row;
    numberCol=col;
    m_handler=rowHandler;

    RowData::m_Handler = m_handler;

    for(int i=0;i<numberRow;i++)
    {
            RowData* dat = new RowData(numberCol);
            m_gridData.insert(i, dat);
    }
    m_handler->createRowHeader(m_Headers);
    // model in model
    m_hasModel    = false;
    m_subHandler  = NULL;

}

int MFATableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_gridData.count();
}

int MFATableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return numberCol;
}

QVariant MFATableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        RowData* dat =m_gridData.at(index.row());
        int col = index.column();
        if(dat != NULL)
            return dat->getData(col);
    }
    else if(role == Qt::EditRole)
    {
        RowData* dat =m_gridData.at(index.row());
        int col = index.column();
        if(dat != NULL)
         return dat->getData(col);
    }
    else if(role == Qt::BackgroundRole)
    {
        RowData* dat =m_gridData.at(index.row());
        if(!(dat->isValid()))
         return QVariant(QColor(255, 0, 0, 127));
    }
    return QVariant();
}

bool MFATableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        RowData* dat =m_gridData.at(index.row());
        dat->setData(index.column(), value.toString());

        //--debug only
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row= 0; row < m_gridData.count(); row++)
        {
            for(int col= 0; col < numberCol; col++)
            {
                dat =m_gridData.at(row);
                result +=dat->getData(col)+ " ";
            }
            result +="\n";
        }
        qDebug(result.toStdString().c_str());
        //--end debug only

        emit editCompleted( result );
    }
    return true;
}

Qt::ItemFlags MFATableModel::flags(const QModelIndex & index) const
{
    for(int i=0;i<m_editableColumn.count();i++){
        if(m_editableColumn[i]==index.column()){
            return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
        }
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
}


bool MFATableModel::insertRows ( int row, int count, const QModelIndex & parent )
{
    beginInsertRows(parent, row, row+count-1);
    RowData::m_Handler = m_handler;
    for (int n = 0; n < count; ++n) {
        RowData* dat = new RowData(numberCol);
        m_gridData.insert(row, dat);

        if(m_hasModel){
            if(m_subHandler==NULL){
                std::cout<<" WARNING: m_subHandler is NULL"<<std::endl;
            }
            MFATableModel* childModel = new MFATableModel(this,0,6,m_subHandler);
            RowData::m_Handler = m_handler;
            childModel->AddEditableColumn(2);
            childModel->AddEditableColumn(3);
            m_listModel.insert(row,childModel);
        }
    }
    endInsertRows();

    return true;
}

bool MFATableModel::removeRows ( int row, int count, const QModelIndex & parent )
{
    beginRemoveRows(parent, row,row+count-1);

    if(row <= m_gridData.count()-1)
    {
        for (int n = 0; n < count; ++n) {
                delete m_gridData.at(row);
                m_gridData.removeAt(row);
                if(m_hasModel){
                    delete m_listModel.at(row);
                    m_listModel.removeAt(row);
                }
            }
    }
    endRemoveRows ();
    return true;
}

QVariant MFATableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();
    if(orientation == Qt::Vertical)
       return QVariant(section);
    if (m_Headers.size() ==0)
        return QVariant();
    return m_Headers.at(section);

}

bool MFATableModel::cloneRow(int row)
{
    RowData::m_Handler = m_handler;

    RowData* dat= m_gridData.at(row);
    insertRows(row+1,1);
    // take row data from new inserted row
    RowData* newRowData =m_gridData.at(row+1);

    for(int i=0;i<numberCol;i++)
    {
        if(i>1) //don't clone idx & ID // todo :don't hardcoded
        {
            newRowData->setData(i,dat->getData(i));
        }
    }
    if(this->m_hasModel){

        MFATableModel* sourceModel = getModel(row);
        MFATableModel* destModel = getModel(row+1);

        destModel->copyContent(sourceModel);
    }
    return true;
}

bool MFATableModel::swapRow(int row1,int row2)
{
   //TODO : swap data

   return true;
}

RowData* MFATableModel::getDatainRow(int iRow)
{
    return m_gridData.at(iRow);
}

void MFATableModel::timerHit()
{
/*
*/
}

void MFATableModel::refresh() // <-- todo: need optimize this, for speed. now refresh all.
{
     QModelIndex topLeft  = createIndex(0,0);
     QModelIndex botright = createIndex(m_gridData.count(),numberCol-1);

     emit dataChanged(topLeft, botright);
}

void MFATableModel::clearData()
{
    int rCount = m_gridData.count();
    for(int i= rCount; i >=0 ; --i)
    {
        removeRows(i,1);
    }
}

MFATableModel* MFATableModel::getModel(int rowN)
{
    return m_listModel.at(rowN);
}

MFATableModel::~MFATableModel(){
    int totalChild = m_listModel.count();

    for (int n = 0; n < totalChild; ++n) {
            delete m_listModel.at(n);
            m_gridData.removeAt(n);
        }
}

void MFATableModel::copyContent(MFATableModel* otherModel)
{
   for(int i=0;i<otherModel->rowCount();i++){
       this->insertRows(i,1);

       RowData* _rowDataSrc = otherModel->getDatainRow(i);
       RowData* _rowDataDest = this->getDatainRow(i);

       for(int j=0;j<numberCol;j++)
       {
           _rowDataDest->setData(j,_rowDataSrc->getData(j));
       }
   }
}
