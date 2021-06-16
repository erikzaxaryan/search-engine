#ifndef PAGE_LOADER_H
#define PAGE_LOADER_H

#include <string>
#include "Page.hpp"

class PageLoader {
private:
    static size_t getData(char* buffer,size_t size, size_t n, std::string* data);
public:
    
    PageLoader();

    Page Load(const std::string& url);
};
#endif
