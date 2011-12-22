#include "rowdatahandler.h"
#include "uidmanager.h"

/* module */
void ModuleRowDataHandler::createDefaultRow(std::vector<QString> &vec,int col)
{
    QString s="0";
    if(col==0)
        s=QString::number(1);//m_IDModule
    else if(col==1)
        s=QString::number(100+(UID::Instance().getLastUID(UIDType::MODULE)));
    else if(col==4)
        s=QString::number(32);
    else if(col==5)
        s=QString::number(32);
    vec.push_back(s);
}

void ModuleRowDataHandler::createRowHeader(QStringList& strList)
{
    strList.push_back("Index ");
    strList.push_back("ID");
    strList.push_back("X");
    strList.push_back("Y");
    strList.push_back("Width");
    strList.push_back("Height");
}


/* frame */
void FrameRowDataHandler::createDefaultRow(std::vector<QString> &vec,int col)//,std::vector<ModuleFrame*>&Table)
{
    QString s="0";
    if(col==0)
        s=QString::number(1);
    else if(col==1)
        s=QString::number(1000+(UID::Instance().getLastUID(UIDType::FRAME)));
    else if(col==4)
        s=QString::number(32);
    else if(col==5)
        s=QString::number(32);
    vec.push_back(s);

    //moduleFrame_ = new ModuleFrame();
    //Table.push_back(moduleFrame_);
}

void FrameRowDataHandler::createRowHeader(QStringList& strList)
{
    strList.push_back("Index ");
    strList.push_back("Frm ID");
    strList.push_back("N Mod");
    strList.push_back("Name");
    strList.push_back("next");
    strList.push_back("next");
}

/* frame description */
void FrameDescRowDataHandler::createDefaultRow(std::vector<QString> &vec,int col)
{
    QString s="0";
    if(col==0)
        s=QString::number(1);
    else if(col==1)
        s=QString::number(2000+1);
    else if(col==4)
        s=QString::number(32);
    else if(col==5)
        s=QString::number(32);
    vec.push_back(s);
}

void FrameDescRowDataHandler::createRowHeader(QStringList& strList)
{
    strList.push_back("Index ");
    strList.push_back("Mod ID");
    strList.push_back("offset X");
    strList.push_back("offset Y");
    strList.push_back("next");
    strList.push_back("next");
}

