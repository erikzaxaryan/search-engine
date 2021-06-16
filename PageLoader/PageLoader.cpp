#include "PageLoader.hpp"

#include <iostream>
#include <stdio.h>
#include <curl/curl.h>


PageLoader::PageLoader() {}

std::string res;



Page PageLoader::Load(const std::string& url)
{
    
    CURL* curl = curl_easy_init();

    CURLcode requestResultat = CURLE_NO_CONNECTION_AVAILABLE;

    std::string result{};
    long status = 0;

    std::string effectiveUrl;
    
    if(curl)
    {
        

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    
        requestResultat = curl_easy_perform(curl);

        if (requestResultat == CURLE_OK)
        {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            
            char* url = nullptr;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

            if (url != nullptr)
            {
                effectiveUrl.append(url);
            }
            
        }else
        {
            //error
        }
        
        curl_easy_cleanup(curl);
    }

    return Page(effectiveUrl, result, status, requestResultat);
}

size_t PageLoader::getData(char* buffer,size_t size, size_t n, std::string* data) {
    size_t bytes = size * n;
    for (size_t i = 0; i < bytes; i++)
    {
        res += buffer[i];
    }
    return bytes;
}

int main(void) {
    PageLoader request;
    Page response = request.Load("https://www.google.com");
    std::cout << response.getBody();   
}

