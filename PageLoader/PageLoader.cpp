#include "PageLoader.hpp"




PageLoader::PageLoader() {}

std::string res;

size_t getData(char* buffer,size_t size, size_t n, void* _) {
    size_t bytes = size * n;   
    for (size_t i = 0; i < bytes; i++)
    {
        res += buffer[i];
    }   
    return bytes;
}

Page PageLoader::Load(const std::string& url)
{
    res = "";

    CURL* curl = curl_easy_init();

    if(curl == nullptr)
    {
        std::cerr << "curl initialize faild";
        return Page();
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);

    CURLcode result = curl_easy_perform(curl);
    
    if (result != CURLE_OK)
    {
        std::cerr << "Failed!";
    }
    
    long status;

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
    
    curl_easy_cleanup(curl);
    
    
    return Page(res, status);
}



