#include "Page.hpp"

Page::Page(){}

Page::Page(const std::string body, int status)
{
    this->body = body;
    this->status = status;
}

const std::string& Page::getBody() const 
{
    return this -> body;
}

int Page::getStatus() const 
{
    return this -> status;
}