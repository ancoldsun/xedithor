#include "rowdata.h"

RowDataHandler* RowData::m_Handler=0;

RowData::RowData(int numbData ):m_IDModule(mLast_ID_Module++)
{
    for(int i=0;i<numbData;i++)
    {
        m_Handler->createDefaultRow(m_ColData,i);
    }
}
RowData::~RowData()
{
}
QString RowData::getData(const int nCol)
{
    return m_ColData.at(nCol);
}
void RowData::setData(const int nCol, const QString data)
{
    m_ColData[nCol] = data;
}
