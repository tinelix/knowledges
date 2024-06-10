/*  Tinelix Knowledges - encyclopedia in your console
 *  -------------------------------------------------------------------------------------------
 *  Copyright � 2024 Dmitry Tretyakov (aka. Tinelix)
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

#include "extwnd.h"

ExtWindowCtrl::ExtWindowCtrl() {
    hWidth = 8;
    hHeight = 8;
    gCtrlSize = 0;
    gChildWndsSize = 0;
    hCtrls = (UIControl**)malloc(sizeof(UIControl) * 255);
    hChildWnds = (ExtWindowCtrl**)malloc(sizeof(ExtWindowCtrl) * 16);
}

ExtWindowCtrl::ExtWindowCtrl(char* pId) {
    #ifdef _MSVC
        sprintf_s(id, strlen(pId), "%s", pId);
    #else
        sprintf(id, "%s", pId);
    #endif
    hWidth = 8;
    hHeight = 8;
    gCtrlSize = 0;
    gChildWndsSize = 0;
    hCtrls = (UIControl**)malloc(sizeof(UIControl) * 255);
    hChildWnds = (ExtWindowCtrl**)malloc(sizeof(ExtWindowCtrl) * 16);
}

ExtWindowCtrl::ExtWindowCtrl(char* pId, ExtWindowCtrl* pParent) {
    #ifdef _MSVC
        sprintf_s(id, strlen(pId), "%s", pId);
    #else
        sprintf(id, "%s", pId);
    #endif
    hWidth = 8;
    hHeight = 8;
    gCtrlSize = 0;
    gChildWndsSize = 0;
    hCtrls = (UIControl**)malloc(sizeof(UIControl) * 255);
    hChildWnds = (ExtWindowCtrl**)malloc(sizeof(ExtWindowCtrl) * 16);
    gParent = pParent;
}

ExtWindowCtrl::~ExtWindowCtrl() {
    free(hCtrls);
    free(hChildWnds);
}

void ExtWindowCtrl::addControl(UIControl* pCtrl) {
    hCtrls[gCtrlSize] = pCtrl;
    gCtrlSize++;
}

void ExtWindowCtrl::addControl(UIControl* pCtrl, int index) {
    hCtrls[gCtrlSize] = pCtrl;
    if (gCtrlSize >= index)
        gCtrlSize++;
}

void ExtWindowCtrl::addChildWindow(char* id, char* title, int width, int height, int x, int y) {

    ExtWindowCtrl* pExtWnd = new ExtWindowCtrl(id, this);

    int realWidth = 5;
    int realHeight = 5;

    realWidth = width;
    if (width <= 5) {
        realWidth = 5;
    }
    else {
        realWidth = width;
    }

    if (height <= 5) {
        realHeight = 5;
    }
    else {
        realHeight = height;
    }

    pExtWnd->hWnd = newwin(realHeight, realWidth, y + 1, x + 1);

    #ifdef _MSVC
        sprintf_s(pExtWnd->hTitle, "%s", title);      // <-- store window text in ExtWindow object
    #else
        sprintf(pExtWnd->hTitle, "%s", title);      // <-- store window text in ExtWindow object
    #endif

    pExtWnd->hWidth = realWidth;
    pExtWnd->hHeight = realHeight;

    box(pExtWnd->hWnd, 0, 0);                   // <-- draw window borders

    mvwprintw(                                  // <-- draw window text in top border area
        pExtWnd->hWnd,
        0, (pExtWnd->hWidth - strlen(pExtWnd->hTitle) - 4) / 2,
        "\u2524 %s \u251c", pExtWnd->hTitle
    );

    wbkgd(pExtWnd->hWnd, COLOR_PAIR(2));

    keypad(pExtWnd->hWnd, true);
    wrefresh(pExtWnd->hWnd);

    hChildWnds[gChildWndsSize] = pExtWnd;

    gChildWndsSize++;
}

int ExtWindowCtrl::getControlsSize() {
    return gCtrlSize;
}

int ExtWindowCtrl::getChildWindowsSize() {
    return gChildWndsSize;
}

void ExtWindowCtrl::redraw() {
    touchwin(hWnd);
    wrefresh(hWnd);
}

void ExtWindowCtrl::clear() {
    wclear(hWnd);
    box(hWnd, 0, 0);
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        0, (hWidth - strlen(hTitle) - 4) / 2,
        "\u2524 %s \u251c", hTitle
    );
}

void ExtWindowCtrl::freeWnd() {
    wclear(hWnd);
    wrefresh(hWnd);
    delwin(hWnd);
    refresh();
}

void ExtWindowCtrl::listen(bool value) {

}

void ExtWindowCtrl::onKeyPressed(char k) {

}

void ExtWindowCtrl::onKeyPressed(char k, char prev_key) {

}

