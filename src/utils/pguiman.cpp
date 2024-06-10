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

#include "pguiman.h"

char key;

#ifdef _WIN32
int* winver;
#endif

/* Initializes ncurses screen. */

PseudoGUIManager::PseudoGUIManager(IPseudoGUIManager* pInterface) {
    setlocale(LC_ALL, "");                      /* <-- set locale for correct non-ASCII characters
                                                       displaying */
    screen = initscr();                         /* <-- temporally clearing command prompt and initializes
                                                       empty screen of ncurses */
    keypad(screen, true);                       // <-- enables arrow pressed keys handling

    noecho();                                   /* <-- disables escaping of characters typed on the
                                                       keyboard                                     */
    curs_set(0);                                // <-- makes the terminal cursor invisible

    // Creates a color that will be used later if its output is supported by the terminal.

    if (has_colors()) {
        start_color();
    #ifdef _WIN32
        winver = KnowledgesVersion::getWindowsVersion();

        if (winver[0] <= 10 && winver[2] <= 19041) { // if Windows lower than 10 2004
            init_pair(1, COLOR_LIGHT_CYAN_4BIT, COLOR_BLACK);
            init_pair(3, COLOR_WHITE, COLOR_DARK_GRAY_4BIT);
            init_pair(4, COLOR_WHITE, COLOR_RED);
            init_pair(5, COLOR_WHITE, COLOR_GREEN);
            init_pair(6, COLOR_GREEN, COLOR_WHITE);
            init_pair(7, COLOR_GREEN, COLOR_DEEP_BLACK);
            init_pair(8, COLOR_RED, COLOR_BLACK);
            init_pair(9, COLOR_BLACK, COLOR_WHITE);
            init_pair(10, COLOR_BLACK, COLOR_BLACK);

            bkgd(COLOR_PAIR(3));
        }
        else {
    #endif
            init_color(COLOR_LIGHT_WHITE, 768, 768, 768);
            init_color(COLOR_BLUE_SKY, 0, 142, 768);  //  <-- create RGB value for COLOR_BLUE_SKY variable
            init_pair(1, COLOR_LIGHT_WHITE, COLOR_BLUE_SKY);
            init_color(COLOR_GRAY, 384, 384, 384);  //  <-- create RGB value for COLOR_GRAY variable
            init_pair(2, COLOR_LIGHT_WHITE, COLOR_GRAY);
            init_color(COLOR_DEEP_BLACK, 0, 0, 0);  //  <-- create RGB value for COLOR_DEEP_BLACK variable
            init_pair(3, COLOR_LIGHT_WHITE, COLOR_DEEP_BLACK);
            init_color(COLOR_RED, 255, 0, 0);  //  <-- create RGB value for COLOR_RED variable
            init_pair(4, COLOR_LIGHT_WHITE, COLOR_RED);
            init_color(COLOR_DARK_GREEN, 0, 255, 0);  //  <-- create RGB value for COLOR_GREEN variable
            init_pair(5, COLOR_LIGHT_WHITE, COLOR_DARK_GREEN);
            init_pair(6, COLOR_LIGHT_GREEN, COLOR_GRAY);
            init_pair(7, COLOR_LIGHT_GREEN, COLOR_DEEP_BLACK);
            init_color(COLOR_LIGHT_RED, 768, 120, 120);
            init_pair(8, COLOR_LIGHT_RED, COLOR_DEEP_BLACK);
            init_color(COLOR_DARK_GRAY, 255, 255, 255);
            init_pair(9, COLOR_DARK_GRAY, COLOR_GRAY);
            init_pair(10, COLOR_DARK_GRAY, COLOR_DEEP_BLACK);

            bkgd(COLOR_PAIR(3));
    #ifdef _WIN32
        }
    #endif
    }

    

    gInterface = pInterface;

    getmaxyx(screen, gActiveHeight, gActiveWidth);
}

/* Shows version info and copyright in console top area. */

void PseudoGUIManager::showTopVersionInfo() {

    char* verStr = KnowledgesVersion::getVersion();
    const char* verInfoStr = "Tinelix Knowledges v. %s | Copyright (C) 2024 Dmitry Tretyakov";

    /*      int int
     * move( y , x )                                                <-- moves cursor
     *
     *              const char*
     * printw("String [%s/%d/%f/%c]", [args])                       <-- print text in screen
     *
     *         int int   int     attr_t    short   const void *
     * mvchgat( y , x, length, attributes, color,    options   )    <-- set text attributes or colors
     *                                                                  attrubutes: A_BLANK, A_BOLD,
     *                                                                              A_NORMAL
     *                                                                  color: number from init_pair(),
     *                                                                         argument #0
     */

    move(0, (gActiveWidth - strlen(verInfoStr) - strlen(verStr) + 2) / 2);
    printw(verInfoStr, verStr);

    mvchgat(0, 0, -1, A_NORMAL, 1, NULL);  // sets the background color for a specific line

    refresh();
}

/* Listens pressed keys on keyboard. */

void PseudoGUIManager::listenKeyboard() {
    key = getch();
    gInterface->onKeyPressed(key);
}

void PseudoGUIManager::listenKeyboard(ExtWindowCtrl* hWndCtrl) {
    key = wgetch(hWndCtrl->hWnd);
    gInterface->onKeyPressed(key, hWndCtrl);
}

WINDOW* PseudoGUIManager::getScreen() {
    return screen;
}

/* Freeing ncurses:
 * 'delete [object];' calling '[ClassName]::~[ClassName]()' function.
 */

PseudoGUIManager::~PseudoGUIManager() {
    endwin();
    delscreen((SCREEN*)screen);
}
