#include "Page.hpp"


Page::Page(const std::string& url, const std::string& body, long status, CURLcode error)
{
    this->url = url;
    this->body = body;
    this->status = status;
    this->error = error;
}

const std::string& Page::getBody() const 
{
    return this -> body;
}
CURLcode Page::isError() const 
{
    return this -> error;
}
const std::string& Page::getURL() const 
{
    return this -> url;
}
long Page::getStatus() const 
{
    return this -> status;
}