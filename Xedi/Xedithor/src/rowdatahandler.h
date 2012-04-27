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

#ifndef ROWDATAHANDLER_H
#define ROWDATAHANDLER_H

#include <QStringList>
#include <QString>

#include <string>
#include <vector>

/* abstract class
*  for customizable data
*/
class RowDataHandler
{
public:
    virtual void createDefaultRow(std::vector<QString>& vec,int col)=0;
    virtual void createRowHeader(QStringList& strList)=0;
};

/* module data */
class ModuleRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};

/* frame data */
class FrameRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};
/* frame desc data */
class FrameDescRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};

/* anim data */
class AnimRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};
/* anim desc data */
class AnimDescRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};


#endif // ROWDATAHANDLER_H
