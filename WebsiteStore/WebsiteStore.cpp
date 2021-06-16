#include <iostream>

#include "WebsiteStore.hpp"
#include "Website.hpp"

WebsiteStore::WebsiteStore()
{
    sql::ResultSet* resultSet = DBConnector::ExecuteQuery("SELECT * FROM Crawler.websites;");

    while(resultSet->next())
    {
        int id = resultSet->getInt("id");
        std::string domain = resultSet->getString("domain");
        std::string url = resultSet->getString("url");

        uint32_t lastCrawlingTime;
        lastCrawlingTime = resultSet->getUInt("lastCrawlingTime");
        std::cout << std::endl << resultSet->getInt(1) << " " << domain << " " << url << " " << lastCrawlingTime << std::endl;
        this->add(Website(id, domain, url, lastCrawlingTime));
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
    allWebs.insert({website.getUrl(), website});
}
//Update
void WebsiteStore::update(const Website& website)
{
    DBConnector::ExecuteQuery("UPDATE Crawler.websites SET lastCrawlingTime = current_timestamp() WHERE domain = '" + website.getDomain() + "'" );
}
