#include "knowbase.h"
#include <cstdio>

KnowledgeBase::KnowledgeBase(char* pFileName) {

    gCategoriesCount = 0;

    FILE *fp = fopen(pFileName, "r");
    size_t maxFileSize = 1048576;               // max. 1 MB

    gTitle = new char[100];

    gBuffer = (char*) malloc(sizeof(char) * maxFileSize);

    if(fp) {
        fread(gBuffer, sizeof(char) * maxFileSize, SEEK_CUR, fp);

        if(gReader.parse(gBuffer, gValues, false)) {                // <-- parsing from JSON file
            gTkwn0 = gValues["tknw0"];                              // <-- accessing to JSON object
            Json::Value jTitle = gTkwn0["title"];                    // <-- accessing to JSON string
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
    gCategories = (struct KBCategory**) malloc(jCategories.size() * sizeof(KBCategory));
    gCategoriesCount = jCategories.size();
    for(int i = 0; i < jCategories.size(); i++) {
        Json::Value jCategory = jCategories[i];
        gCategories[i] = new KBCategory();
        sprintf(gCategories[i]->title, "%s", jCategory["title"].asString().c_str());
    }

    return gCategories;
}
//
// struct KBArticle* KnowledgeBase::getArticle(int pId) {
//
// }

int KnowledgeBase::getCategoriesCount() {
    return gCategoriesCount;
}
