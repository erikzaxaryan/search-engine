#ifndef Link_hpp
#define Link_hpp

#include <string>
#include <ctime>
#include "LinkStatus.hpp"

class Link 
{
private:

    std::string url;

    std::string domain;

    LinkStatus status;

public:
    Link();

    Link(const std::string& url, const std::string& domain, const LinkStatus status);

    std::string getUrl() const;

    std::string getDomain() const;

    LinkStatus getStatus() const;

    friend bool operator==(const Link& a, const Link& b);
};




#endif