/*  Tinelix Knowledges - encyclopedia in your console
 *  -------------------------------------------------------------------------------------------
 *  Copyright © 2024 Dmitry Tretyakov (aka. Tinelix)
 *
 *  This file is part of Tinelix Knowledges program.
 *
 *  Tinelix Knowledges is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU Affero General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License along with this
 *  program. If not, see https://www.gnu.org/licenses/.
 *
 *  Source code: https://github.com/tinelix/knowledges
 */

#ifndef KNOWLEDGES_UTILS_KNOWBASE_H
#define KNOWLEDGES_UTILS_KNOWBASE_H

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstring>

#include <json/json.h>

struct KBArticle {
    char                        title[100];
    int                         modifiedDate;
    char*                       content;
};

struct KBCategory {
    int                         id;
    char                        title[25];
    struct KBArticle**          articles;
    int                         articlesCount;
};

class KnowledgeBase {
    public:
        KnowledgeBase(char* pFileName);
        ~KnowledgeBase();
        struct KBCategory**     getCategories();
        struct KBArticle**      getArticles(int pCategoryIndex);
        int                     getCategoriesCount();
        int                     getArticlesCount(int pCategoryIndex);
        char*                   getTitle();
        int                     getState();
        char*                   getErrorMessageText();
    private:
        struct KBCategory**     gCategories;
        int                     gCategoriesCount;
        Json::Reader            gReader;
        Json::Value             gValues;
        Json::Value             gTkwn0;
        char*                   gTitle;
        char*                   gBuffer;
        int                     gState;
};

#endif
