#ifndef KNOWLEDGES_WINDOWS_KNOWBASE_H
#define KNOWLEDGES_WINDOWS_KNOWBASE_H

#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif
#include <cstdio>
#include <wchar.h>

#include "../controls/uictrl.h"
#include "../controls/extwnd.h"
#include "../controls/listbox.h"

#include "../utils/knowbase.h"

class KnowledgeBaseWnd : ExtWindowCtrl {
    public:
        KnowledgeBaseWnd(struct KnowledgeBase* pKb);
        ~KnowledgeBaseWnd();
        void onKeyPressed(char k);
    private:
        KnowledgeBase*  gKb;
        KBCategory**    gKbCategories;
        KBArticle*      gKbArticles;
        void prepare();
        void readKnowledgeBase();
        int gActiveWidth, gActiveHeight;
};

#endif
