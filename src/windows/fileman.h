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

#ifndef OPENDSS_WINDOWS_FILEMAN_H
#define OPENDSS_WINDOWS_FILEMAN_H

#include <stdio.h>
#include <stdlib.h>
#ifdef __MINGW64__
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif
#include <tinydir.h>
#include <wchar.h>

#ifdef __MINGW64__
    #include <nstddef.h>
    #include <sys/stat.h>
#endif

#include "../controls/uictrl.h"
#include "../controls/extwnd.h"
#include "../controls/listbox.h"
#include "../controls/msgbox.h"

#include "../utils/fileman.h"

#include "../interfaces/fileman.h"


class FileManagerWnd : public ExtWindowCtrl {
    public:
        FileManagerWnd(FileManager *pFileMan, IFileManager *pInterface);
        char* getSelectedFileName();
        void onKeyPressed(char k);
        void onDirectoryRead(tinydir_file* files);
        void onFileManResult(int cmdId, int resultCode);
        void onFileManError(int cmdId, int errorCode);
        void listen(bool value);
        bool disableListening;
    private:
        FileManager     *gFileMan;
        IFileManager    *gInterface;
        char            *gSelectedFileName;
};
#endif
