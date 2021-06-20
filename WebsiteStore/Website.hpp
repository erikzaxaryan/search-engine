#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include <string>

class Website
{
private:

    std::string url;

    std::string domain;

public:

    Website(const std::string& domain,const std::string& url);

    const std::string& getUrl() const;

    const std::string& getDomain() const;
};


#endif