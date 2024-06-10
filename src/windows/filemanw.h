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

#pragma once

#ifdef _MSVC		/* If it turns out that we are building a 
					   project using Microsoft Visual Studio. */
	#ifdef _PDCURSES
		#include <curses.h>
	#else
		#include <ncurses.h>
	#endif
#else
	#ifdef __PDCURSES__
		#include <curses.h>
	#elif __MINGW64__
		#include <ncurses/ncurses.h>
	#else
		#include <ncurses.h>
	#endif
#endif

#include <tinydir.h>

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include <controls/uictrl.h>
#include <controls/extwnd.h>
#include <controls/listbox.h>
#include <controls/msgbox.h>
#include <utils/extstr.h>
#include <utils/fileman.h>
#include <interfaces/fileman.h>

class FileManagerWnd : public ExtWindowCtrl
{
	public:
		FileManagerWnd(FileManager* pFileMan, IFileManager* pInterface, WINDOW* screen);
		char* getSelectedFileName();
		void listen(bool value);
		void onKeyPressed(char k);
		void onDirectoryRead(tinydir_file* files);
		void onFileManResult(int cmdId, int resultCode);
		void onFileManError(int cmdId, int errorCode);
		bool disableListening;
	private:
		FileManager* gFileMan;
		IFileManager* gInterface;
		char* gSelectedFileName;
};

