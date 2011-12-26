#include "rowdatahandler.h"
#include "uidmanager.h"

#define MODULE_START_ID 1000
#define FRAME_START_ID 3000
#define ANIM_START_ID 5000

/* module */
void ModuleRowDataHandler::createDefaultRow(std::vector<QString> &vec,int col)
{
    QString s="0";
    if(col==0)
        s=QString::number(0);//m_IDModule
    else if(col==1)
        s=QString::number(MODULE_START_ID+(UID::Instance().getLastUID(UIDType::MODULE)));
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
        s=QString::number(FRAME_START_ID+(UID::Instance().getLastUID(UIDType::FRAME)));
    else if(col==4)
        s="N/A";//QString::number(32);
    else if(col==5)
        s="N/A";//QString::number(32);
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
        s="N/A";//QString::number(32);
    else if(col==5)
        s="N/A";//QString::number(32);
    vec.push_back(s);
}

void FrameDescRowDataHandler::createRowHeader(QStringList& strList)
{
    strList.push_back(" UID ");
    strList.push_back("Mod ID");
    strList.push_back("offset X");
    strList.push_back("offset Y");
    strList.push_back("next");
    strList.push_back("next");
}

