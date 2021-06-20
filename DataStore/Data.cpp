#include "Data.hpp"

Data::Data(){}

Data::Data(const std::string& url, const std::string& title, const std::string& description, const std::string& allText){
    this->url = url;
    this->title = title;
    this->description = description;
    this->allText = allText;    
}

const std::string& Data::getUrl() const {
    return this->url;
}

const std::string& Data::getDescription() const {
    return this->description;
}

const std::string& Data::getTitle() const {
    return this->title;
}

const std::string& Data::getAllText() const {
    return this->allText;
}