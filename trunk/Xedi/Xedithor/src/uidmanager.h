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

#ifndef UIDMANAGER_H
#define UIDMANAGER_H

#include <iostream>

namespace UIDType
{
    const int MODULE  = 0;
    const int FRAME   = 1;
    const int ANIM    = 2;
    const int FRAME_DESC   = 3;
    const int ANIM_DESC   = 4;
    const int UIDType_MAX =5;
}

class UID
{
private:
    static UID* m_instance;
    int m_uid[UIDType::UIDType_MAX];
    bool m_isAutoInc;
    UID();
public:
    static UID& Instance();
    void setAutoInc(bool val){
        m_isAutoInc=val;
    }

    void setLastUID(int lastUid,int typeUID);
    int getLastUID(int typeUID);
    void resetUID();
};

#endif // UIDMANAGER_H
