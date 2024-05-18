#ifndef KNOWLEDGES_INTERFACES_PGUIMAN_H
#define KNOWLEDGES_INTERFACES_PGUIMAN_H

#include "../controls/extwnd.h"

class IPseudoGUIManager {
    public:
        IPseudoGUIManager() {};
        virtual ~IPseudoGUIManager() {};
        virtual void onKeyPressed(char k) = 0;
        virtual void onKeyPressed(char k, ExtWindowCtrl* pExtWnd) = 0;
};

#endif // KNOWLEDGES_INTERFACES_PGUIMAN_H
