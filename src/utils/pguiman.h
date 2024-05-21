#ifndef KNOWLEDGES_UTILS_PGUIMAN_H
#define KNOWLEDGES_UTILS_PGUIMAN_H

#ifdef __CYGWIN_MINGW64__
    #include <ncurses.h>
#elif __MINGW64__
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

#define COLOR_GRAY 242
#define COLOR_DARK_GREEN 28
#define COLOR_DEEP_BLACK 16

class PseudoGUIManager {
    public:
        PseudoGUIManager(IPseudoGUIManager *interface);
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

#endif // KNOWLEDGES_UTILS_PGUIMAN_H
