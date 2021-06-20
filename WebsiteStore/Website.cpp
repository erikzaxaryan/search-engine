#include "Website.hpp"

Website::Website(const std::string& domain, const std::string& url) {
    this->domain = domain;
    this->url = url;
}

const std::string& Website::getDomain() const {
    return this->domain;
}

const std::string& Website::getUrl() const {
    return this->url;
}

