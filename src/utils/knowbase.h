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
