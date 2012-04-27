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

#ifndef GLOBALCONSTANT_H
#define GLOBALCONSTANT_H

namespace CMainWindow
{
    const int MIN_WIDTH_LEFT_DOCK = 350;
    const int COUNT_COLUMN_TABLE  = 6;
}
namespace XD
{
    const int T_MODULE  = 0;
    const int T_FRAME   = 1;
    const int T_ANIM    = 2;
    const int NUM_TAB   = 3;

    const int GROUP1    = 0;
    const int GROUP2    = 1;
    const int NUM_GROUP = 3;

    const int B_ADD     = 0;
    const int B_CLONE   = 1;
    const int B_DEL     = 2;
    const int B_UP      = 3;
    const int B_DOWN    = 4;
    const int B_TOP     = 5;
    const int B_BOTTOM  = 6;
    const int NUM_BUTTON=7;

    const int TABLE1    = 0;
    const int TABLE2    = 1;
    const int NUM_TABLE = 2;
}

namespace Page
{
    const int MODULE  = 0;
    const int FRAME   = 1;
    const int ANIM    = 2;
    const int SEQANIM    = 3;
}
const int WidthRectView  = 4000;
const int HeightRectView = 4000;

namespace TabView
{
    const int MODULE = 0;
    const int FRAME  = 1;
    const int ANIM   = 2;
}

namespace SETUPTABLE
{
    const int RowCount =0;
    const int ColCount =6;
}

namespace ITEM_PIXMAP
{
    const int Max_W=500;
    const int Max_H=500;
}

namespace C_UID
{
    const int MODULE_START  = 1000;
    const int FRAME_START   = 3000;
    const int ANIM_START    = 5000;
}

namespace DMOD
{
    const int IDX    = 0;
    const int UID    = 1;
    const int PX     = 2;
    const int PY     = 3;
    const int WIDTH  = 4;
    const int HEIGHT = 5;

    const int MFIELD = 6;
}

namespace DFRM
{
    const int IDX    = 0;
    const int PX     = 1;
    const int PY     = 2;
    const int WIDTH  = 3;
    const int HEIGHT = 4;
    const int MFIELD = 5;
}

namespace DANIM
{
    const int MFIELD = 5;
}

const int default_fps = 10;
const int millisecond = 1000;
const QString string_fps ="   FPS: ";

#endif // GLOBALCONSTANT_H
