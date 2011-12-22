/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/
#ifndef ROWDATA_H
#define ROWDATA_H

#include <iostream>
#include <vector>
#include <qstring.h>

#include "rowdatahandler.h"

/* module in frame */
/*
class ModuleFrame
{
public:
  QString getData(const int nCol){
      return m_ColData.at(nCol);
  }

  void setData(const int nCol, const QString data){
      m_ColData[nCol] = data;
  }

private:
  std::vector<QString> m_ColData;
  int m_IDModule;
};
*/

class RowData
{
  public:
    RowData(int numbData,RowDataHandler* handler);
    RowData(int numbData);
    static RowDataHandler* m_Handler;

    ~RowData();
    QString getData(const int nCol);
    void setData(const int nCol, const QString data);

    /*std::vector<ModuleFrame*> getTable(){
        return m_listRow;
    }
    */

  private:
    std::vector<QString> m_ColData;
   //std::vector<ModuleFrame*> m_listRow; // row in row :D, use for row that have list of row

    int m_IDModule;
  public:
    static int mLast_ID_Module;

};


#endif // ROWDATA_H
