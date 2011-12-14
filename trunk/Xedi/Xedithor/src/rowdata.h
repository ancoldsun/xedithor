/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/
#ifndef ROWDATA_H
#define ROWDATA_H

#include <iostream>
#include <vector>
#include <qstring.h>

class RowData
{
  public:
    RowData(int numbData ):m_IDModule(mLast_ID_Module++)
    {
        for(int i=0;i<numbData;i++)
        {
            QString s="0";
            if(i==0)
                s=QString::number(m_IDModule);
            else if(i==1)
                s=QString::number(100+m_IDModule);
            else if(i==4)
                s=QString::number(32);
            else if(i==5)
                s=QString::number(32);
            m_ColData.push_back(s);
        }
    }
    ~RowData()
    {
    }
    QString getData(const int nCol)
    {
        return m_ColData.at(nCol);
    }
    void setData(const int nCol, const QString data)
    {
        m_ColData[nCol] = data;
    }

  private:
    std::vector<QString> m_ColData;
    int m_IDModule;
  public:
    static int mLast_ID_Module;

};


#endif // ROWDATA_H
