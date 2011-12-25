#ifndef UIDMANAGER_H
#define UIDMANAGER_H

#include <iostream>

namespace UIDType
{
    const int MODULE  = 0;
    const int FRAME   = 1;
    const int ANIM    = 2;
    const int UIDType_MAX =3;
}

class UID
{
private:
    static UID* m_instance;
    int m_uid[UIDType::UIDType_MAX];
    bool m_isAutoInc;
public:
    UID();
    static UID& Instance();
    void setAutoInc(bool val){
        m_isAutoInc=val;
    }

    void setLastUID(int lastUid,int typeUID);
    int getLastUID(int typeUID);
};

#endif // UIDMANAGER_H
