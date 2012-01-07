// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
#ifndef ROWDATA_H
#define ROWDATA_H

#include <iostream>
#include <vector>
#include <qstring.h>

#include "rowdatahandler.h"

class RowData: public QObject
{
  public:
    RowData(int numbData,RowDataHandler* handler);
    RowData(int numbData);
    static RowDataHandler* m_Handler;

    ~RowData();
    QString getData(const int nCol);
    void setData(const int nCol, const QString data);
    void setValid(bool val){
        isValidData=val;
    }
    bool isValid(){
        return isValidData;
    }

  private:
    std::vector<QString> m_ColData;
    bool isValidData;
    int m_IDModule;
  public:
    static int mLast_ID_Module;
};


#endif // ROWDATA_H
