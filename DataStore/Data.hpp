#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data
{
private:
    
    std::string url;
    std::string title;
    std::string description;
    std::string allText;

public:

    Data();

    Data(const std::string& url, const std::string& title, const std::string& description, const std::string& allText);

    const std::string& getUrl() const;

    const std::string& getTitle() const;
    
    const std::string& getDescription() const;
    
    const std::string& getAllText() const;
};

#endif