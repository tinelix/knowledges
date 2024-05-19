#include "knowbase.h"

KnowledgeBase::KnowledgeBase(char* pFileName) {
    FILE *fp = fopen(pFileName, "r");
    char* buffer;
    size_t fileSize = 16384;

    if(fp) {

        buffer = (char*) malloc(sizeof(char) * fileSize);
        size_t pkSize = fread(buffer, sizeof(char) * fileSize, 1, fp);

        if(gReader.parse(buffer, gValues, false)) {                // <-- Parsing from JSON file
            Json::Value jTitle = gValues.get("title", "[Unnamed Knowledge Base]");
            gTitle = new char[128];
            sprintf(gTitle, "%s", jTitle.asString().c_str());
        }
    }

    free(buffer);
}

KnowledgeBase::~KnowledgeBase() {

}

char* KnowledgeBase::getTitle() {
    return gTitle;
}

// struct KBCategories** KnowledgeBase::getCategories() {
//
// }
//
// struct KBArticle* KnowledgeBase::getArticle(int pId) {
//
// }

int KnowledgeBase::getCategoriesCount() {
    return gCategoriesCount;
}
