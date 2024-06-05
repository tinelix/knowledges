/*  Tinelix Knowledges - encyclopedia in your console
 *  -------------------------------------------------------------------------------------------
 *  Copyright © 2024 Dmitry Tretyakov (aka. Tinelix)
 *
 *  This file is part of Tinelix Knowledges program.
 *
 *  Tinelix Knowledges is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this
 *  program. If not, see https://www.gnu.org/licenses/.
 *
 *  Source code: https://github.com/tinelix/knowledges
 */

#ifndef KNOWLEDGES_CONTROLS_LISTBOX_H
#define KNOWLEDGES_CONTROLS_LISTBOX_H

#include "extwnd.h"
#include "uictrl.h"
#include "../utils/extstr.h"
#include <cstring>
#include <cstdio>

#ifdef __PDCURSES__
    #include <curses.h>
#elif __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

struct ListItem {
    char title[384];
    void* ptr;
    struct ListItem** subItems;
    int subItemsCount;
    bool expanded;
    bool subItem;
};

class ListBoxCtrl : UIControl {
    public:
        ListBoxCtrl(ExtWindowCtrl* pParent, int pItemCount, bool pTrackPos);
        ~ListBoxCtrl();
        void addListItem(int index, ListItem* item);
        int getSelectionIndex();
        void setSelectionIndex(int index);
        void onKeyPressed(char k);
        void drawListPointer(int x, int y, bool isVisible);
        void drawListPointer(int x, int y, char p, bool isVisible);
        void goToPage(int pPageNumber);
        void recreate(int pItemCount);
        void expand(int pIndex, bool status);
        struct ListItem** getItems();
        int getPageNumber();
        int getItemsCount();
        int getSubItemsCount(int pIndex);
        int hX, hY, hWidth, hHeight, hExpandedItemIndex, hSubItemCount;
        bool expanded;
    protected:
        struct ListItem**   gListItems;
        bool gTrackPos;
        int getVirtualSelectionIndex();
        ExtWindowCtrl* gParent;
        int gSelectionIndex, gPageNumber, gItemCount;
};

#endif
