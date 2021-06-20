#include "Link.hpp"

//Def constructor
Link::Link()
{
    url = "";
}

Link::Link(const std::string& url, const std::string& domain, const LinkStatus status)
{
    this->url = url;
    this->domain = domain;
    this->status = status;
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


bool operator== (const Link& left, const Link& right)
{
    return left.getUrl() == right.getUrl();
}