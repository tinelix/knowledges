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

#pragma once

#define KNOWLEDGES_VERSION "0.0.1"

#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #include <ntstatus.h>

    typedef LONG NTSTATUS, * PNTSTATUS;
    #define STATUS_SUCCESS (0x00000000)

    typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
#endif

class KnowledgesVersion {
public:
    static char* getVersion() {
        char* version = new char[24];
        #ifdef _MSVC
            sprintf_s(version, 24, "%s", KNOWLEDGES_VERSION);
        #else
            sprintf(version, "%s", KNOWLEDGES_VERSION);
        #endif

        return version;
    }

    #ifdef _WIN32
        static int* getWindowsVersion() { // Correct getting Windows OS version
            int* version = new int[3];

            version[0] = -1;
            version[1] = -1;
            version[2] = -1;

            HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");

            if (hMod) {
                RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
                if (fxPtr != NULL) {
                    RTL_OSVERSIONINFOW rovi = { 0 };
                    rovi.dwOSVersionInfoSize = sizeof(rovi);
                    if (STATUS_SUCCESS == fxPtr(&rovi)) {
                        version[0] = rovi.dwMajorVersion;
                        version[1] = rovi.dwMinorVersion;
                        version[2] = rovi.dwBuildNumber;
                    }
                }
            }
            
            return version;
        }
    #endif
};
