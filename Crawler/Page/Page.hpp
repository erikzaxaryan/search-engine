#ifndef PAGE_HPP
#define PAGE_HPP


#include <string>
#include <curl/curl.h>


class Page {
private:
// Effective url
    std::string url;
// All Htmls Doc
    std::string body;
// Html response code
    long status;
// Value of request
    CURLcode error;
public:
// Creates a page with a given body, status and error
    Page (const std::string& url, const std::string& body, long status, CURLcode error);

    CURLcode isError() const;

    const std::string& getBody() const;

    long getStatus() const;

    const std::string& getURL() const;
};

#endif