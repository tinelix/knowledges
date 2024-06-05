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

#ifndef OPENDSS_CONTROLS_EXTWND_H
#define OPENDSS_CONTROLS_EXTWND_H

#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include "uictrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class ExtWindowCtrl {
    public:
        ExtWindowCtrl();
        ExtWindowCtrl(char* pId);
        ExtWindowCtrl(char* pId, ExtWindowCtrl* pParent);
        ~ExtWindowCtrl();
        char hTitle[255], id[60];
        int hWidth, hHeight;
        WINDOW* hWnd;
        UIControl** hCtrls;
        ExtWindowCtrl** hChildWnds;
        ExtWindowCtrl* gParent;
        void addControl(UIControl* pCtrl);
        void addControl(UIControl* pCtrl, int index);
        void addChildWindow(char* id, char* title, int width, int height, int x, int y);
        int getControlsSize();
        int getChildWindowsSize();
        void redraw();
        void clear();
        virtual void freeWnd();
        virtual void listen(bool value);
        virtual void onKeyPressed(char k);
        virtual void onKeyPressed(char k, char prev_k);
    private:
        int gCtrlSize;
        int gChildWndsSize;
};

#endif
