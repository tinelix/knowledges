#include "knowbase.h"
#include <cstddef>
#include <cstdio>

KnowledgeBase::KnowledgeBase(char* pFileName) {
    #ifdef _MSVC
        FILE* fp;
        fopen_s(&fp, pFileName, "r");
    #else
        FILE* fp = fopen(pFileName, "r");
    #endif

    size_t maxFileSize = 1048576;               // max. 1 MB

    gCategoriesCount = 0;

    gBuffer = (char*) malloc(sizeof(char) * maxFileSize);

    if(fp) {
        fread(gBuffer, sizeof(char) * maxFileSize, SEEK_CUR, fp);
        if(gReader.parse(gBuffer, gValues, false)) {                // <-- parsing from JSON file
            gTkwn0 = gValues["tknw0"];                              // <-- accessing to JSON object
            Json::Value jTitle = gTkwn0["title"];                   // <-- accessing to JSON string
            #ifdef _MSVC
                sprintf_s(gTitle, 100, "%s", jTitle.asString().c_str());       // <-- convert to char* object
            #else
                sprintf(gTitle, "%s", jTitle.asString().c_str());       // <-- convert to char* object
            #endif
        } else {
            gState = -1;
            #ifdef _MSVC
                sprintf_s(gTitle, 80, "JSON Error");
            #else
                sprintf(gTitle, "JSON Error");
            #endif
        }
        fclose(fp);
    } else {
        gState = -2;
        #ifdef _MSVC
            sprintf_s(gTitle, 80, "File Error");
        #else
            sprintf(gTitle, "File Error");
        #endif
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
        (struct KBCategory**) malloc(60 * sizeof(KBCategory));
    gCategoriesCount = jCategories.size();

    for(int i = 0; i < (int)jCategories.size(); i++) {
        if (i >= 60) {
            break;
        }
        Json::Value jCategory = jCategories[i];
        gCategories[i] = new KBCategory();
        #ifdef _MSVC
            sprintf_s(gCategories[i]->title, 80, "%s", jCategory["title"].asString().c_str());
        #else
            sprintf(gCategories[i]->title, "%s", jCategory["title"].asString().c_str());
        #endif
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
        #ifdef _MSVC
            sprintf_s(gCategories[pCategoryIndex]->articles[i]->title,
                    80, "%s", jArticles[i]["title"].asString().c_str());
            sprintf_s(gCategories[pCategoryIndex]->articles[i]->content,
                    256, "%s", jArticles[i]["content"].asString().c_str());
        #else
            sprintf(gCategories[pCategoryIndex]->articles[i]->title,
                "%s", jArticles[i]["title"].asString().c_str());
            sprintf(gCategories[pCategoryIndex]->articles[i]->content,
                "%s", jArticles[i]["content"].asString().c_str());
        #endif
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
