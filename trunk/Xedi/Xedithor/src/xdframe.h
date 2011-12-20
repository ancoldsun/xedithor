#ifndef XDFRAME_H
#define XDFRAME_H

#include <QString>
#include <QList>
#include "rowdata.h"

class xdFrame
{
public:
    xdFrame();
    ~xdFrame();
    void addModules(int mID);
    void removeModules(int mID);
    void cloneModule();
    void setfid(QString id);
    void setName(QString name);

    inline QString fid(){
        return m_fid;
    }
    inline int totalModules(){
        return m_nModules;
    }
    inline QString name(){
        return m_name;
    }

private:
    QString m_fid;
    int m_nModules;
    QString m_name;
    QList<RowData*> m_listModules;
};

#endif // XDFRAME_H
