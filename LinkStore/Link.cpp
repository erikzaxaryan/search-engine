#include "Link.hpp"

//Def constructor
Link::Link()
{
    url = "";
}

Link::Link(int id,const std::string& url, const std::string& domain, const LinkStatus status, const time_t lastLoadTime)
{
    this->id = id;
    this->url = url;
    this->domain = domain;
    this->status = status;
    this->lastLoadTime = lastLoadTime;
}

time_t Link::getLastTime() const {
    return this->lastLoadTime;
}

std::string Link::getUrl() const {
    return this->url;
}

std::string Link::getDomain() const {
    return this->domain;
}

LinkStatus Link::getStatus() const {
    return this->status;
}

int Link::getId() const {
    return this->id;
}

bool operator== (const Link& left, const Link& right)
{
    return left.getUrl() == right.getUrl();
}