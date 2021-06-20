#ifndef PAGE_LOADER_H
#define PAGE_LOADER_H

#include <string>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include "Page.hpp"

class PageLoader {
public:
    
    PageLoader();

    Page Load(const std::string& url);
};
#endif
