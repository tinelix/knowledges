#include "knowbase.h"

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

    ListBoxCtrl* categoriesListBox = new ListBoxCtrl(categoriesWnd, categoriesSize, false);

    categoriesListBox->hY = 2;
    categoriesListBox->hX = 2;
    categoriesListBox->hWidth = categoriesWnd->hWidth - 4;
    categoriesListBox->hHeight = categoriesWnd->hHeight - 4;

    categoriesListBox->setSelectionIndex(0);

    for(int i = 0; i < categoriesSize; i++) {
        ListItem* item = new ListItem();
        sprintf(item->title, "%s", gKbCategories[i]->title);
        item->subItems = (ListItem**) malloc(gKb->getArticlesCount(i) * sizeof(ListItem));
        KBArticle** articles = gKb->getArticles(i);
        item->subItemsCount = gKb->getArticlesCount(i);
        for(int i2 = 0; i2 < gKb->getArticlesCount(i); i2++) {
            item->subItems[i2] = new ListItem();
            sprintf(item->subItems[i2]->title, "%s", articles[i2]->title);
        }
        categoriesListBox->addListItem(i, item);
    }

    wrefresh(categoriesWnd->hWnd);

    categoriesWnd->addControl((UIControl*)categoriesListBox);

    char k = wgetch(categoriesWnd->hWnd);
    onKeyPressed(k);
}

void KnowledgeBaseWnd::onKeyPressed(char k) {
    ExtWindowCtrl* categoriesWnd = hChildWnds[0];
    ExtWindowCtrl* articleWnd = hChildWnds[1];

    scrollok(articleWnd->hWnd, TRUE);

    ListBoxCtrl* categoriesListBox = ((ListBoxCtrl*) categoriesWnd->hCtrls[0]);
    categoriesListBox->onKeyPressed(k);

    if(k != 'q') {
        int xItemIndex = categoriesListBox->hExpandedItemIndex;
        if(k == (int)10 && categoriesListBox->expanded) {
            int itemIndex = categoriesListBox->getSelectionIndex();
            int subItemIndex = itemIndex - xItemIndex - 1;

            ListItem* item = categoriesListBox->getItems()[xItemIndex];

            if(itemIndex > xItemIndex && subItemIndex < item->subItemsCount) {
                ListItem* childItem = item->subItems[subItemIndex];
                KBArticle** articles = gKb->getArticles(xItemIndex);

                for(int x = 1; x < articleWnd->hWidth - 1; x++) {
                    for(int y = 1; y < articleWnd->hHeight - 1; y++) {
                        mvwaddch(articleWnd->hWnd, y, x, ' ');
                    }
                }

                mvwprintw(articleWnd->hWnd, 2, 2, "%s", childItem->title);

                char* articleContent = articles[subItemIndex]->content;
                char* articleContentWrap;

                int articleLinesCount = ExtString::strlines(
                    articleContent, ExtString::strcrlfc(articleContent)
                );

                char** articleLines;

                articleLines = ExtString::strsplitln(articleContent);

                for(int i = 0; i < articleLinesCount; i++) {
                    mvwprintw(
                        articleWnd->hWnd, 4 + i, 2,
                        "%s",
                        articleLines[i]
                    );
                }

                wrefresh(articleWnd->hWnd);
            }
        }
        k = wgetch(categoriesWnd->hWnd);
        onKeyPressed(k);
    } else {

    }
}

KnowledgeBaseWnd::~KnowledgeBaseWnd() {
    wclear(hWnd);
    delwin(hWnd);
}


