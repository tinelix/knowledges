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

#include "filemanw.h"

#define MAX_FILENAME_LENGTH 32

ListBoxCtrl* mFileListBox;

FileManagerWnd::FileManagerWnd(
    FileManager* pFileMan, IFileManager* pInterface, WINDOW* screen
) {
    #ifdef _MSVC
        sprintf_s(hTitle, "File Manager");
        sprintf_s(id, "fileManWnd");
    #else
        sprintf(hTitle, "File Manager");
        sprintf(id, "fileManWnd");
    #endif

    gFileMan = pFileMan;
    gInterface = pInterface;
    hScreen = screen;

    int gActiveWidth, gActiveHeight;

    getmaxyx(hScreen, gActiveHeight, gActiveWidth);

    hWidth = gActiveWidth - 2;
    hHeight = gActiveHeight - 3;

    hWnd = newwin(hHeight, hWidth,
        ((gActiveHeight - hHeight) / 2) + 1,
        (gActiveWidth - hWidth) / 2);

    keypad(hWnd, true);

    box(hWnd, 0, 0);                            // <-- draw window borders
    mvwprintw(                                  // <-- draw window text in top border area
        hWnd,
        0, (gActiveWidth - wcslen((wchar_t*)hTitle)) / 2.5,
        "\u2524 %s \u251c", hTitle
    );

    wbkgd(hWnd, COLOR_PAIR(2));

    wrefresh(hWnd);

    disableListening = false;
}

char* FileManagerWnd::getSelectedFileName() {
    return gSelectedFileName;
}

void FileManagerWnd::onKeyPressed(char k) {
    if (k == 'q') {
        disableListening = false;
        return;
    }

    ListBoxCtrl* mFileListBox = ((ListBoxCtrl*)hCtrls[0]);
    char fname[384];

    tinydir_file file = gFileMan->getFile(
        mFileListBox->getSelectionIndex()
    );

    #ifdef _MSVC
        sprintf_s(
            fname, 384, "%s/%s", 
            gFileMan->getRealPath(gFileMan->getCurrentPath()), 
            file.name
        );
    #else
        sprintf(
            fname, "%s/%s", 
            gFileMan->getRealPath(gFileMan->getCurrentPath()), 
            file.name
        );
    #endif

   if (k == (int)10) {
        if (file.is_dir) { // if it's directory
            gFileMan->readDir(fname);
        }
        else if (ExtString::strendq(fname, ".mp3")) {
            char msgTitle[] = "Opening file";
            MessageBoxU* pMsgBox = new MessageBoxU(
                msgTitle, fname, 5, hScreen
            );
            ((ExtWindowCtrl*)pMsgBox)->freeWnd();
            redraw();
            gSelectedFileName = fname;
            disableListening = true;
            gInterface->onResult(1, 0);
        }
    } else {
        mFileListBox->onKeyPressed(k);
    }

    if (!disableListening) {
        k = wgetch(hWnd);
        onKeyPressed(k);
    }
}

void FileManagerWnd::onDirectoryRead(tinydir_file* files) {
    for (int x = 2; x <= hWidth - 2; x++) {
        mvwaddch(hWnd, 2, x, ' ');
    }

    mvwprintw(hWnd, 2, 2, "%s", gFileMan->getRealPath(gFileMan->getCurrentPath()));
    if (mFileListBox == NULL) {
        mFileListBox = new ListBoxCtrl(this, gFileMan->getFilesCount(), true);
    }
    else {
        mFileListBox->recreate(gFileMan->getFilesCount());
    }
    mFileListBox->setSelectionIndex(0);
    mFileListBox->hY = 4;
    mFileListBox->hX = 2;
    mFileListBox->hHeight = hHeight - 6;
    mFileListBox->hWidth = hWidth - 4;

    addControl((UIControl*)mFileListBox, 0);

    for (int y = 0; y < mFileListBox->hHeight; y++) {
        for (int x = 0; x < mFileListBox->hWidth; x++) {
            mvwaddch(hWnd, mFileListBox->hY + y, mFileListBox->hX + x, ' ');
        }
    }

    for (int i = 0; i < gFileMan->getFilesCount(); i++) {
        ListItem* item = new ListItem();
        #ifdef _MSVC
            sprintf_s(item->title, 256, "%s", files[i].name);
        #else
            sprintf(item->title, "%s", files[i].name);
        #endif
        if (strlen(item->title) > MAX_FILENAME_LENGTH) {
            ExtString::strcut(item->title, MAX_FILENAME_LENGTH - 3, -1);
            #ifdef _MSVC
                sprintf_s(item->title + MAX_FILENAME_LENGTH - 3, strlen(item->title), "...");
            #else
                sprintf(item->title + MAX_FILENAME_LENGTH - 3, "...");
            #endif
        }
        if (i <= mFileListBox->hHeight
            && ExtString::strendq((char*)files[i].name, ".mp3")) {
            char full_fname[600];
            #ifdef _MSVC
                sprintf_s(
                    full_fname, 384, "%s/%s", 
                    gFileMan->getRealPath(gFileMan->getCurrentPath()), 
                    files[i].name
                );
            #else
                sprintf(
                    full_fname, "%s/%s", 
                    gFileMan->getRealPath(gFileMan->getCurrentPath()), 
                    files[i].name
                );
            #endif
            /*AudioTager* pTagger = new AudioTager();
            AudioTags* data = pTagger->readTags(full_fname);
            if (data) {
                mvwprintw(
                    hWnd,
                    mFileListBox->hY + i,
                    MAX_FILENAME_LENGTH + 19,
                    "%s - %s",
                    data->artist, data->title
                );
            }*/
        }
        mFileListBox->addListItem(i, item);
    }

    wrefresh(hWnd);

    char k = wgetch(hWnd);

    onKeyPressed(k);
}

void FileManagerWnd::onFileManResult(int cmdId, int resultCode) {
    if (cmdId == 0) {
        clear();
        mvwprintw(hWnd, 2, 2, "%s", 
            gFileMan->getRealPath(
                gFileMan->getCurrentPath()
            )
        );
    }
}

void FileManagerWnd::onFileManError(int cmdId, int errorCode) {

}

void FileManagerWnd::listen(bool value) {
    disableListening = !value;
}
