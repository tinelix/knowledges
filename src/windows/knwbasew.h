#pragma once

#include <controls/extwnd.h>

#include <cstdio>
#include <wchar.h>

#include <controls/uictrl.h>
#include <controls/extwnd.h>
#include <controls/listbox.h>

#include <utils/knowbase.h>

class KnowledgeBaseWnd : ExtWindowCtrl
{
    public:
        KnowledgeBaseWnd(struct KnowledgeBase* pKb, WINDOW* screen);
        ~KnowledgeBaseWnd();
        void onKeyPressed(char k);
    private:
        KnowledgeBase* gKb;
        KBCategory** gKbCategories;
        KBArticle* gKbArticles;
        void prepare();
        void readKnowledgeBase();
        int gActiveWidth, gActiveHeight;
};

