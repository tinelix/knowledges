#include "knowbase.h"
#include <cstdio>
#include <curses.h>

KnowledgeBaseWnd::KnowledgeBaseWnd(struct KnowledgeBase* pKb) {

    gKb = pKb;

    sprintf(id, "msgBoxWnd");
    sprintf(hTitle, "%s", pKb->getTitle());

    getmaxyx(stdscr, gActiveHeight, gActiveWidth);

    hWidth = gActiveWidth - 2;
    hHeight = gActiveHeight - 3;

    hWnd = newwin(hHeight, hWidth,
                  ((gActiveHeight - hHeight) / 2) + 1,
                  (gActiveWidth - hWidth) / 2);

    keypad(hWnd, true);

    box(hWnd, 0, 0);                            // <-- draw window borders
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        0, (gActiveWidth - wcslen((wchar_t*)hTitle)) / 2.5,
        "\u2524 %s \u251c", hTitle
    );

    wbkgd(hWnd, COLOR_PAIR(2));

    wrefresh(hWnd);

    prepare();

}

void KnowledgeBaseWnd::prepare() {

    hCtrls = (UIControl**)malloc(sizeof(UIControl) * 255);
    hChildWnds = (ExtWindowCtrl**)malloc(sizeof(ExtWindowCtrl) * 16);

    // Categories child window

    char categoriesWndId[] = "categoriesWndId";
    char categoriesWndTitle[] = "Categories";

    addChildWindow(categoriesWndId, categoriesWndTitle, 26, hHeight - 3, 2, 3);

    // Article child window

    char articleWndId[] = "articleWndId";
    char articleWndTitle[] = "Article";

    addChildWindow(articleWndId, articleWndTitle, hWidth - 31, hHeight - 3, 29, 3);

    wrefresh(hWnd);

    readKnowledgeBase();

}

void KnowledgeBaseWnd::readKnowledgeBase() {
    gKbCategories = gKb->getCategories();

    int categoriesSize = gKb->getCategoriesCount();

    ExtWindowCtrl* categoriesWnd = hChildWnds[0];

    ListBoxCtrl* categoriesListBox = new ListBoxCtrl(categoriesWnd, categoriesSize);

    categoriesListBox->hY = 4;
    categoriesListBox->hX = 2;
    categoriesListBox->hWidth = categoriesWnd->hWidth - 4;
    categoriesListBox->hHeight = categoriesWnd->hHeight - 4;

    categoriesListBox->setSelectionIndex(0);

    for(int i = 0; i < categoriesSize; i++) {
        ListItem* item = new ListItem();
        sprintf(item->title, "%s", gKbCategories[i]->title);
        categoriesListBox->addListItem(i, item);
    }

    wrefresh(categoriesWnd->hWnd);

    categoriesWnd->addControl((UIControl*)categoriesListBox);

    char k = wgetch(categoriesWnd->hWnd);
    onKeyPressed(k);
}

void KnowledgeBaseWnd::onKeyPressed(char k) {
    ExtWindowCtrl* categoriesWnd = hChildWnds[0];
    ((ListBoxCtrl*) categoriesWnd->hCtrls[0])->onKeyPressed(k);
    if(k != 'q') {
        k = wgetch(categoriesWnd->hWnd);
        onKeyPressed(k);
    }
}

KnowledgeBaseWnd::~KnowledgeBaseWnd() {
    wclear(hWnd);
    delwin(hWnd);
}


