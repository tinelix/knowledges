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

#ifndef KNOWLEDGES_UTILS_PGUIMAN_H
#define KNOWLEDGES_UTILS_PGUIMAN_H

#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../interfaces/pguiman.h"
#include "../controls/extwnd.h"
#include <locale.h>
#include "../version.h"

#define COLOR_LIGHT_WHITE       255
#define COLOR_GRAY              240
#define COLOR_DARK_GRAY         235
#define COLOR_DARK_GREEN         28
#define COLOR_DEEP_BLACK         16
#define COLOR_LIGHT_RED          82
#define COLOR_LIGHT_GREEN        47
#define COLOR_BLUE_SKY           68

class PseudoGUIManager {
    public:
        PseudoGUIManager(IPseudoGUIManager *pInterface);
        ~PseudoGUIManager();
        void showTopVersionInfo();
        void listenKeyboard();
        void listenKeyboard(ExtWindowCtrl *pExtWnd);
        ExtWindowCtrl* createWindow(char* id, char* title, int width, int height, bool alignCenter);
        void clearWindow(ExtWindowCtrl* pExtWnd);
        void drawText(ExtWindowCtrl *wnd, char* text, int x, int y);
        int gActiveWidth, gActiveHeight;
    private:
        IPseudoGUIManager   *gInterface;
        ExtWindowCtrl       *gWnd;
        char                gWndTitle[255];
};

#endif // OPENDSS_UTILS_PGUIMAN_H
