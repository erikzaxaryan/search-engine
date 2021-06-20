#ifndef PAGE_HPP
#define PAGE_HPP


#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>


class Page {
private:

// All Htmls Doc
    std::string body;
// Html response code
    int status;
public:

    Page();

// Creates a page with a given body and status
    Page (std::string body, int status);


    const std::string& getBody() const;

    int getStatus() const;

};

#endif