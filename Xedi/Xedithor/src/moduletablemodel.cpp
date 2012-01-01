
#include "moduletablemodel.h"

int RowData::mLast_ID_Module=0;

ModuleTableModel::ModuleTableModel(QObject *parent,int row,int col,RowDataHandler* rowHandler)
    :QAbstractTableModel(parent)
{
    numberRow=row;
    numberCol=col;
    m_handler=rowHandler;

    RowData::m_Handler = m_handler;

    for(int i=0;i<numberRow;i++)
    {
            RowData* dat = new RowData(numberCol);
            m_gridData2.insert(i, dat);
    }
    m_handler->createRowHeader(m_Headers);
    // model in model
    m_hasModel    = false;
    m_subHandler  = NULL;

}

int ModuleTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_gridData2.count();
}

int ModuleTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return numberCol;
}

QVariant ModuleTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        RowData* dat =m_gridData2.at(index.row());
        int col = index.column();
        if(dat != NULL)
            return dat->getData(col);
    }
    else if(role == Qt::EditRole)
    {
        RowData* dat =m_gridData2.at(index.row());
        int col = index.column();
        if(dat != NULL)
         return dat->getData(col);
    }

    return QVariant();
}

bool ModuleTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        qDebug("test");
        //save value from editor to member m_gridData
        RowData* dat =m_gridData2.at(index.row());
        dat->setData(index.column(), value.toString());
        //m_gridData[index.row()][index.column()] = value.toString();

        //--debug only
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row= 0; row < m_gridData2.count(); row++)
        {
            for(int col= 0; col < numberCol; col++)
            {
                dat =m_gridData2.at(row);
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

Qt::ItemFlags ModuleTableModel::flags(const QModelIndex & index) const
{
    for(int i=0;i<m_editableColumn.count();i++){
        if(m_editableColumn[i]==index.column()){
            return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
        }
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
}


bool ModuleTableModel::insertRows ( int row, int count, const QModelIndex & parent )
{
    beginInsertRows(parent, row, row+count-1);
    RowData::m_Handler = m_handler;
    for (int n = 0; n < count; ++n) {
        RowData* dat = new RowData(numberCol);
        m_gridData2.insert(row, dat);

        if(m_hasModel){
            // danger : no code will delete : new FrameDescRowDataHandler
            // todo   : make singleton for row handler
            if(m_subHandler==NULL){
                std::cout<<" WARNING: m_subHandler is NULL"<<std::endl;
            }
            ModuleTableModel* childModel = new ModuleTableModel(this,0,6,m_subHandler);
            RowData::m_Handler = m_handler;
            childModel->AddEditableColumn(2);
            childModel->AddEditableColumn(3);
            m_listModel.insert(row,childModel);
        }
    }
    endInsertRows();

    return true;
}

bool ModuleTableModel::removeRows ( int row, int count, const QModelIndex & parent )
{
    beginRemoveRows(parent, row,row+count-1);

    if(row <= m_gridData2.count()-1)
    {
        for (int n = 0; n < count; ++n) {
                delete m_gridData2.at(row);
                m_gridData2.removeAt(row);
                if(m_hasModel){
                    delete m_listModel.at(row);
                    m_listModel.removeAt(row);
                }
            }
    }
    endRemoveRows ();
    return true;
}

QVariant ModuleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //std::cout<<"removeRows: "<<QVariant(section).Double<<std::endl;

    if (role != Qt::DisplayRole)
            return QVariant();
    if(orientation == Qt::Vertical)
       return QVariant(section);
    if (m_Headers.size() ==0)
        return QVariant();
    return m_Headers.at(section);

}

bool ModuleTableModel::cloneRow(int row)
{
    RowData::m_Handler = m_handler;

    RowData* dat= m_gridData2.at(row);
    insertRows(row+1,1);
    RowData* newRowData =m_gridData2.at(row+1);
    delete newRowData;
    newRowData = new RowData(numberCol);
    for(int i=0;i<numberCol;i++)
    {
        if(i>1) //don't clone idx & ID
        {
            newRowData->setData(i,dat->getData(i));
        }
    }
    return true;
}

bool ModuleTableModel::swapRow(int row1,int row2)
{
   //TODO : swap data

   return true;
}

RowData* ModuleTableModel::getDatainRow(int iRow)
{
    return m_gridData2.at(iRow);
}

void ModuleTableModel::timerHit()
{
/*
*/
}

void ModuleTableModel::refresh() // <-- need optimize this, for speed. now refresh all.
{
     QModelIndex topLeft  = createIndex(0,0);
     QModelIndex botright = createIndex(m_gridData2.count(),numberCol-1);

     emit dataChanged(topLeft, botright);
}

void ModuleTableModel::clearData()
{
    std::cout<<"row count: "<<m_gridData2.count()<<std::endl;
    int rCount = m_gridData2.count();
    for(int i= rCount; i >=0 ; --i)
    {
        std::cout<<"delete: "<<i<<std::endl;
        removeRows(i,1);
    }
}

ModuleTableModel* ModuleTableModel::getModel(int rowN)
{
    return m_listModel.at(rowN);
}

ModuleTableModel::~ModuleTableModel(){
    int totalChild = m_listModel.count();

    for (int n = 0; n < totalChild; ++n) {
            delete m_listModel.at(n);
            m_gridData2.removeAt(n);
        }
}
