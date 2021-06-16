#ifndef Link_hpp
#define Link_hpp

#include <string>
#include <ctime>
#include "LinkStatus.hpp"

class Link 
{
private:

    int id;

    std::string url;

    std::string domain;

    LinkStatus status;

    time_t lastLoadTime;

public:
    Link();

    Link(int id, const std::string& url, const std::string& domain, const LinkStatus status, time_t time);

    time_t getLastTime() const;

    std::string getUrl() const;

    std::string getDomain() const;

    LinkStatus getStatus() const;

    int getId() const;

    friend bool operator==(const Link& a, const Link& b);
};




#endif