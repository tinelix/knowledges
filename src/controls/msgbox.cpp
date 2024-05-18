#include "msgbox.h"
#include <curses.h>

MessageBox::MessageBox(char *pWndTitle, char *pMsgText) {
    sprintf(id, "msgBoxWnd");
    sprintf(hTitle, "%s", pWndTitle);
    sprintf(hMsgText, "%s", pMsgText);

    hWidth = strlen(pMsgText) + 4;
    hHeight = 5;

    int gActiveWidth, gActiveHeight;

    getmaxyx(stdscr, gActiveHeight, gActiveWidth);

    hWnd = newwin(hHeight, hWidth, ((gActiveHeight - hHeight) / 2) + 1, (gActiveWidth - hWidth) / 2);

    keypad(hWnd, true);

    box(hWnd, 0, 0);                            // <-- draw window borders
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        0, (hWidth - strlen(hTitle)) / 2,
        "\u2524 %s \u251c", hTitle
    );

    drawMessageText();

    wbkgd(hWnd, COLOR_PAIR(3));

    wrefresh(hWnd);
}

void MessageBox::drawMessageText() {
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        2, 2,
        "%s", hMsgText
    );
}
