#include <cstring>

#ifdef __CYGWIN_MINGW64__
    #include <ncurses.h>
#elif __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <stdio.h>                  // Linking standard C functions
#include <dirent.h>
#include <unistd.h>

#include "utils/fileman.h"
#include "utils/pguiman.h"
#include "utils/extstr.h"
#include "utils/knowbase.h"

#include "windows/knowbase.h"
#include "windows/fileman.h"

#include "controls/extwnd.h"
#include "controls/listbox.h"
#include "controls/msgbox.h"

#include "interfaces/fileman.h"
#include "interfaces/pguiman.h"

class IKnowledgesFileManager : IFileManager {
    public:
        void onError(int cmdId, int errorCode);
        void onResult(int cmdId, int resultCode);
        void onDirectoryRead(tinydir_file* files);
};

IKnowledgesFileManager          *gFileManInterface;

class IKnowledgesPseudoGUIManager : IPseudoGUIManager {
    public:
        void onKeyPressed(char k) {};
        void onKeyPressed(char k, ExtWindowCtrl *pExtWnd);
};

IKnowledgesPseudoGUIManager     *gPsGUIManInterface;

PseudoGUIManager                *gPsGuiMan;
FileManager                     *gFileMan;

FileManagerWnd                  *gFileManWnd;
KnowledgeBaseWnd                *gKbWnd;

KnowledgeBase                   *gKb;

/* Creates File Manager window and shows directory listing. */

void openFileManager() {
    gFileManWnd = new FileManagerWnd(gFileMan, (IFileManager*)gFileManInterface);
    gFileMan->readCurrentDir();
}

/* Application main function */

int main() {
    gPsGUIManInterface = new IKnowledgesPseudoGUIManager();
    gFileManInterface = new IKnowledgesFileManager();

    gFileMan = new FileManager((IFileManager*)gFileManInterface);
    gPsGuiMan = new PseudoGUIManager((IPseudoGUIManager*)gPsGUIManInterface);

    gPsGuiMan->showTopVersionInfo();

    openFileManager();

    delete gPsGuiMan;
    return 0;
}

void openKnowledgeBase(char* pFileName) {
    gKb = new KnowledgeBase(pFileName);
    gKbWnd = new KnowledgeBaseWnd(gKb);
}

/* Handles File Manager errors. */

void IKnowledgesFileManager::onError(int cmdId, int errorCode) {
    if(cmdId == 0) {
        char msgTitle[] = "Error";
        char msgText[] = "Cannot open this directory!";
        MessageBoxU* pMsgBox = new MessageBoxU(msgTitle, msgText, 4);
        gPsGuiMan->listenKeyboard((ExtWindowCtrl*)pMsgBox);
        ((ExtWindowCtrl*)pMsgBox)->freeWnd();
        gFileManWnd->redraw();
        gPsGuiMan->listenKeyboard((ExtWindowCtrl*) gFileManWnd);
    }
}

/* Handles File Manager successed responses. */

void IKnowledgesFileManager::onResult(int cmdId, int resultCode) {
    gFileManWnd->onFileManResult(cmdId, resultCode);
    if(cmdId == 1) {
        openKnowledgeBase(gFileManWnd->getSelectedFileName());
    }
}

/* Handles File Manager directory list. */

void IKnowledgesFileManager::onDirectoryRead(tinydir_file* files) {
    gFileManWnd->onDirectoryRead(files);
}

/* Handles keyboard pressed keys. */

void IKnowledgesPseudoGUIManager::onKeyPressed(char k, ExtWindowCtrl* pExtWnd) {
    if((int)k == 2 || (int)k == 3) {
        ListBoxCtrl* mFileListBox = ((ListBoxCtrl*)gFileManWnd->hCtrls[0]);
        if(strcmp(pExtWnd->id, "fileManWnd") == 0) {
            if(gFileManWnd->getControlsSize() > 0) {
                mFileListBox->onKeyPressed(k);
            }
        }
    } else if((int)k == 10) { // ENTER key
        if(strcmp(pExtWnd->id, "fileManWnd") == 0
            || strcmp(pExtWnd->id, "articlesListWnd") == 0) {
            if (k == 'q') {
                delete gFileManWnd;
            }
        }
    }
}

