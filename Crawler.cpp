#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "DBConnector/DBConnector.hpp"
#include "WebsiteStore/WebsiteStore.hpp"
#include "LinkStore/LinkStore.hpp"
#include "DataStore/DataStore.hpp"
#include "PageLoader/PageLoader.hpp"
#include "Parser/HTML_Parse.hpp"

int main()
{
    
    std::ios_base::sync_with_stdio(false);
    std::cout.tie();
    
    DBConnector::Initialize("tcp://127.0.0.1:3306", "root", "erebuni11");
    
    WebsiteStore websiteStore;
    DataStore dataStore;
    LinkStore linkStore;
    PageLoader pageLoader;
    
    const auto& websites = websiteStore.getAll();

    for(const auto& website : websites)
    {

        const auto& homepageLink = linkStore.getByUrl(website.getUrl());

        if(homepageLink.has_value())
            linkStore.Save(Link(website.getUrl(), website.getDomain(), LinkStatus::WAITING));
        else    
            linkStore.Save(Link(website.getUrl(), website.getDomain(), LinkStatus::WAITING));

        while(true)
        {
            const auto& links = linkStore.getBy(website.getDomain(), LinkStatus::WAITING, 10);

            if(linkStore.Allloaded())
                break;
            
            for(const auto& link : links)
            {
                Page page = pageLoader.Load(link.getUrl());

                if(page.getStatus() < 200 || page.getStatus() >= 300)
                {
                    linkStore.Save(Link(link.getUrl(), link.getDomain(), LinkStatus::ERROR));
                    continue;
                }

                HTML_Parse parser(link.getUrl(), page.getBody());
                parser.parse();
                
                for(const std::string& u : parser.getUrls())
                {
                    std::cout << u << std::endl;
                }
                Data data(link.getUrl(), parser.getTitle(), parser.getAllText(), parser.getDescription());
                dataStore.addNewData(data);
                for (const auto& newUrl : parser.getUrls())
                {
                    if (linkStore.getByUrl(newUrl).has_value())
                        continue;
                    
                    linkStore.Save(Link(newUrl, link.getDomain(), LinkStatus::WAITING));
                }

                linkStore.Save(Link(link.getUrl(), link.getDomain(), LinkStatus::LOADED));
            }
        }
    }
    std::cout << "\n\n END\n";
    return 0;
}