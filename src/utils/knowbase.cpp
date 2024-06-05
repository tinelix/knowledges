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

#include "knowbase.h"
#include <cstddef>
#include <cstdio>

KnowledgeBase::KnowledgeBase(char* pFileName) {
    FILE *fp = fopen(pFileName, "r");
    size_t maxFileSize = 1048576;               // max. 1 MB

    gCategoriesCount = 0;

    gTitle = new char[100];

    gBuffer = (char*) malloc(sizeof(char) * maxFileSize);

    if(fp) {
        fread(gBuffer, sizeof(char) * maxFileSize, SEEK_CUR, fp);
        if(gReader.parse(gBuffer, gValues, false)) {                // <-- parsing from JSON file
            gTkwn0 = gValues["tknw0"];                              // <-- accessing to JSON object
            Json::Value jTitle = gTkwn0["title"];                   // <-- accessing to JSON string
            sprintf(gTitle, "%s", jTitle.asString().c_str());       // <-- convert to char* object
        } else {
            gState = -1;
            sprintf(gTitle, "JSON Error");
        }
        fclose(fp);
    } else {
        gState = -2;
        sprintf(gTitle, "File Error");
    }

    free(gBuffer);
}

KnowledgeBase::~KnowledgeBase() {

}

char* KnowledgeBase::getTitle() {
    return gTitle;
}

struct KBCategory** KnowledgeBase::getCategories() {
    Json::Value jCategories = gTkwn0["categories"];
    gCategories =
        (struct KBCategory**) malloc(jCategories.size() * sizeof(KBCategory));
    gCategoriesCount = jCategories.size();

    for(int i = 0; i < (int)jCategories.size(); i++) {
        Json::Value jCategory = jCategories[i];
        gCategories[i] = new KBCategory();
        sprintf(gCategories[i]->title, "%s", jCategory["title"].asString().c_str());
    }

    return gCategories;
}

struct KBArticle** KnowledgeBase::getArticles(int pCategoryIndex) {
    Json::Value jCategories = gTkwn0["categories"];
    Json::Value jCategory = jCategories[pCategoryIndex];
    Json::Value jArticles = jCategory["articles"];

    gCategories[pCategoryIndex]->articles =
        (struct KBArticle**) malloc(jArticles.size() * sizeof(KBArticle));

    for(int i = 0; i < (int)jArticles.size(); i++) {
        Json::Value jCategory = jArticles[i];
        gCategories[pCategoryIndex]->articles[i] = new KBArticle();
        gCategories[pCategoryIndex]->articles[i]->content =
            new char[(strlen(jArticles[i]["content"].asString().c_str()) + 4)];

        sprintf(gCategories[pCategoryIndex]->articles[i]->title,
                "%s", jArticles[i]["title"].asString().c_str());
        sprintf(gCategories[pCategoryIndex]->articles[i]->content,
                "%s", jArticles[i]["content"].asString().c_str());
    }

    return gCategories[pCategoryIndex]->articles;
}

int KnowledgeBase::getCategoriesCount() {
    return gCategoriesCount;
}

int KnowledgeBase::getArticlesCount(int pCategoryIndex) {
    Json::Value jCategories = gTkwn0["categories"];
    Json::Value jCategory = jCategories[pCategoryIndex];
    Json::Value jArticles = jCategory["articles"];
    return jArticles.size();
}
