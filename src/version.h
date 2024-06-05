/*  Tinelix OpenDSS - open sourced clone of Digital Sound System player
 *  -------------------------------------------------------------------------------------------
 *  Copyright © 2024 Dmitry Tretyakov (aka. Tinelix)
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of
 *  the GNU General Public License 3 (or any later version) and/or Apache License 2
 *  See the following files in repository directory for the precise terms and conditions of
 *  either license:
 *
 *     LICENSE.APACHE
 *     LICENSE.GPLv3
 *
 *  Please see each file in the implementation for copyright and licensing information,
 *  (in the opening comment of each file).
 */

#ifndef KNOWLEDGES_VERSION_H
#define KNOWLEDGES_VERSION_H

#define KNOWLEDGES_VERSION "0.0.1"

#include <cstdio>

class OpenDSSVersion {
    public:
        static char* getVersion() {
            char* version = new char[24];
            sprintf(version, "%s", KNOWLEDGES_VERSION);

            return version;
        }
};

#endif
