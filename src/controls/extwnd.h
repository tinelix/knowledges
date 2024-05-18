#ifndef KNOWLEDGES_CONTROLS_EXTWND_H
#define KNOWLEDGES_CONTROLS_EXTWND_H

#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include "../utils/uictrl.h"
#include <stdio.h>
#include <stdlib.h>

class ExtWindowCtrl {
public:
    ExtWindowCtrl();
    ExtWindowCtrl(char* pId);
    ~ExtWindowCtrl();
    char hTitle[255], id[60];
    int hWidth, hHeight;
    WINDOW* hWnd;
    UIControl** hCtrls;
    void addControl(UIControl* pCtrl);
    int getControlsSize();
    void freeWnd();
};

#endif
