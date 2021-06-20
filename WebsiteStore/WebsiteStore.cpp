#include <iostream>

#include "WebsiteStore.hpp"
#include "Website.hpp"

WebsiteStore::WebsiteStore()
{
    sql::ResultSet* resultSet = DBConnector::ExecuteQuery("SELECT * FROM Crawler.websites;");
    
    while(resultSet->next())
    {       
        std::string domain = resultSet->getString("domain");
        std::string url = resultSet->getString("url");
        
        std::cout << std::endl << resultSet->getInt(1) << " " << domain << " " << url;
        
        this->add(Website(domain, url));
    }
    
}

//Get all websites
std::vector<Website> WebsiteStore::getAll() const
{
    std::vector<Website> websites;
    for (auto it = allWebs.begin(); it != allWebs.end(); ++it)
    {
        websites.push_back((*it).second);
    }
    
    return websites;
}
//Add new Website
void WebsiteStore::add(const Website& website)
{
    allWebs.insert({ website.getUrl(), website });
}
