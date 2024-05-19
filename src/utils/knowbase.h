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

struct KBCategories {
    int                         id;
    char                        title[25];
    struct KBArticle**          articles;
    int                         articlesCount;
};

class KnowledgeBase {
    public:
        KnowledgeBase(char* pFileName);
        ~KnowledgeBase();
        // struct KBCategories**   getCategories();
        // struct KBArticle*       getArticle(int pId);
        int                     getCategoriesCount();
        char*                   getTitle();
    private:
        struct KBCategories**   gCategories;
        int                     gCategoriesCount;
        Json::Value             gValues;
        Json::Reader            gReader;
        char*                   gTitle;
};

#endif
