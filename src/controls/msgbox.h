#ifndef KNOWLEDGES_CONTROLS_MSGBOX_H
#define KNOWLEDGES_CONTROLS_MSGBOX_H

#include "extwnd.h"
#include "../utils/pguiman.h"
#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

class MessageBox : ExtWindowCtrl {
    public:
        MessageBox(char *pWndTitle, char *pMsgText);
        ~MessageBox();
        void free();
    private:
        void drawMessageText();
        void drawButton();
        char hMsgText[512];
};

#endif
