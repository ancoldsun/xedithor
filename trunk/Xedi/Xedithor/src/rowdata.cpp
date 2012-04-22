#include "rowdata.h"

RowDataHandler* RowData::m_Handler=0;

RowData::RowData(int numbData ):m_IDModule(mLast_ID_Module++)
{
    for(int i=0;i<numbData;i++)
    {
        m_Handler->createDefaultRow(m_ColData,i);
    }
    isValidData=true;
}
RowData::~RowData()
{
}
QString RowData::getData(const int nCol)
{
    if( m_ColData.empty() ||
       (nCol >= m_ColData.size()) ||
        m_ColData.size() > 65000)
        return "0";
    return m_ColData.at(nCol);
}
void RowData::setData(const int nCol, const QString data)
{
    m_ColData[nCol] = data;
}
