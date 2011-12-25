#include "uidmanager.h"

UID* UID::m_instance;

UID::UID()
{
    m_uid[UIDType::MODULE] =0;
    m_uid[UIDType::FRAME]  =0;
    m_uid[UIDType::ANIM]   =0;
    m_isAutoInc =true;
}
UID& UID::Instance()
{
    if(m_instance==NULL)
    {
        m_instance=new UID();
    }
    return *m_instance;
}

void UID::setLastUID(int lastUid,int typeUID)
{
    switch(typeUID)
    {
        case UIDType::MODULE:
            {
                m_uid[UIDType::MODULE]=lastUid;
            }
            break;
        case UIDType::FRAME :
            {
                m_uid[UIDType::FRAME]=lastUid;
            }
            break;
        case UIDType::ANIM  :
            {
                m_uid[UIDType::ANIM]=lastUid;
            }
            break;
    }
}

int UID::getLastUID(int typeUID)
{
    int ret =  m_uid[typeUID];
    if(m_isAutoInc){
        m_uid[typeUID]++;
    }
    return ret;
}
