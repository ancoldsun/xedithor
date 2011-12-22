/* Xedithor : 2D sprite editor
*  Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
*  License  :
*/
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
    void createDefaultRow(std::vector<QString>& vec,int col);///,std::vector<ModuleFrame*>&Table);
    void createRowHeader(QStringList& strList);
};

class FrameDescRowDataHandler :public RowDataHandler
{
public:
    void createDefaultRow(std::vector<QString>& vec,int col);
    void createRowHeader(QStringList& strList);
};


#endif // ROWDATAHANDLER_H
