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

#ifndef KNOWLEDGES_CONTROLS_MSGBOX_H
#define KNOWLEDGES_CONTROLS_MSGBOX_H

#include "extwnd.h"
#include "../utils/pguiman.h"

#ifdef __PDCURSES__
    #include <curses.h>
#elif __MINGW64__
    #include <ncursesw/ncurses.h>
#else
    #include <ncurses.h>
#endif

class MessageBoxU : ExtWindowCtrl {
    public:
        MessageBoxU(char *pWndTitle, char *pMsgText);
        MessageBoxU(char *pWndTitle, char *pMsgText, int pBgColor);
        ~MessageBoxU();
        void free();
    private:
        void drawMessageText();
        void drawButton();
        char hMsgText[512];
};

#endif
