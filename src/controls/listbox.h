#ifndef KNOWLEDGES_CONTROLS_LISTBOX_H
#define KNOWLEDGES_CONTROLS_LISTBOX_H

#include "extwnd.h"
#include "uictrl.h"
#include "../utils/extstr.h"
#include <cstring>

#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

struct ListItem {
    char title[384];
    void* ptr;
    struct ListItem** subItems;
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
        void goToPage(int pPageNumber);
        void recreate(int pItemCount);
        struct ListItem** getItems();
        int getPageNumber();
        int getItemCount();
        int hX, hY, hWidth, hHeight;
    protected:
        struct ListItem**   gListItems;
        bool gTrackPos;
        int getVirtualSelectionIndex();
        ExtWindowCtrl* gParent;
        int gSelectionIndex, gPageNumber, gItemCount;
};

#endif
