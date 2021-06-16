#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include <string>

class Website
{
private:

    int id;

    std::string url;

    std::string domain;

    time_t lastCrawlingTime;

public:

    Website(int id,const std::string& domain,const std::string& url, time_t time);

    int getId() const;

    const std::string& getUrl() const;

    const std::string& getDomain() const;

    time_t getLastCrawlingTime() const;
};


#endif