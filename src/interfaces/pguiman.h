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

#endif // OPENDSS_INTERFACES_PGUIMAN_H
