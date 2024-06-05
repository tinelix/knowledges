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

#ifndef KNOWLEDGES_UTILS_FILEMAN_H
#define KNOWLEDGES_UTILS_FILEMAN_H

#include <tinydir.h>
#include <unistd.h>
#include <interfaces/fileman.h>
#include <controls/listbox.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

class FileManager {
    public:
        FileManager(IFileManager *pInterface);
        ~FileManager();
        void countSlashes(char* pDirPath);
        void readCurrentDir();
        void readDir(char* pDirPath);
        tinydir_file getFile(int index);
        long getFilesCount();
        char* getRealPath(char* pDirPath);
        char* getCurrentPath();

    private:
        IFileManager        *gInterface;
        char                gCurrentPath[384];
        int                 gSelectionIndex;
        tinydir_file        *gFiles;
        long                gFilesCount;
        int                 gPrevSlash;
};

#endif
