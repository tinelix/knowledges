/*  Tinelix Knowledges - encyclopedia in your console
 *  -------------------------------------------------------------------------------------------
 *  Copyright © 2024 Dmitry Tretyakov (aka. Tinelix)
 *
 *  This file is part of Tinelix Knowledges program.
 *
 *  Tinelix Knowledges is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU Affero General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License along with this
 *  program. If not, see https://www.gnu.org/licenses/.
 *
 *  Source code: https://github.com/tinelix/knowledges
 */

#include "msgbox.h"

MessageBoxU::MessageBoxU(char *pWndTitle, char *pMsgText) {
    sprintf(id, "msgBoxWnd");
    sprintf(hTitle, "%s", pWndTitle);
    sprintf(hMsgText, "%s", pMsgText);

    hWidth = strlen(pMsgText) + 4;
    hHeight = 5;

    int gActiveWidth, gActiveHeight;

    getmaxyx(stdscr, gActiveHeight, gActiveWidth);

    hWnd = newwin(hHeight, hWidth,
                  ((gActiveHeight - hHeight) / 2) + 1,
                  (gActiveWidth - hWidth) / 2);

    keypad(hWnd, true);

    box(hWnd, 0, 0);                            // <-- draw window borders
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        0, (hWidth - strlen(hTitle) - 4) / 2,
        "\u2524 %s \u251c", hTitle
    );

    mvwprintw(                                  // <-- draw message text
        hWnd, 2, 2, "%s", hMsgText
    );

    wbkgd(hWnd, COLOR_PAIR(4));

    wrefresh(hWnd);
}

MessageBoxU::MessageBoxU(char *pWndTitle, char *pMsgText, int pBgColor) {
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
        0, (hWidth - strlen(hTitle) - 4) / 2,
        "\u2524 %s \u251c", hTitle
    );

    mvwprintw(                                  // <-- draw message text
        hWnd, 2, 2, "%s", hMsgText
    );

    wbkgd(hWnd, COLOR_PAIR(pBgColor));

    wrefresh(hWnd);
}

void MessageBoxU::drawMessageText() {

}
