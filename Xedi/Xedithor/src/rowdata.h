// Xedithor : 2D sprite editor
// Copyright [2011] Edi Ermawan <edi.ermawan@gmail.Com>

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROWDATA_H
#define ROWDATA_H

#include <iostream>
#include <vector>
#include <qstring.h>

#include "rowdatahandler.h"

class RowData: public QObject
{
       Q_OBJECT
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
