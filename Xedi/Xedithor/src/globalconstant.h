// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//
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
}
const int WidthRectView  = 4000;
const int HeightRectView = 4000;

namespace TabView
{
    const int MODULE = 0;
    const int FRAME  = 1;
    const int ANIM   = 2;
};

namespace SETUPTABLE
{
    const int RowCount =0;
    const int ColCount =6;
}

#endif // GLOBALCONSTANT_H
