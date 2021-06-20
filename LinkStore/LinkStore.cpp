#include <algorithm>
#include <iostream>
#include "LinkStore.hpp"

LinkStore::LinkStore(){}

//alllinks getter
std::vector<Link> LinkStore::getAllLinks() const
{
    return allLinks;
}

//return link by url
std::optional<Link> LinkStore::getByUrl(const std::string& url)
{
    for (const auto& link :allLinks){
        if (link.getUrl() == url)
        {
            return link;
        }
    }
    return{};
}

//return links vector by domain and status
std::vector<Link> LinkStore::getBy(const std::string& domain, LinkStatus status, std::size_t size)
{
    std::vector<Link> links;

    for (int i = 0; i < allLinks.size(); ++i)
    {
        if(size == 0)
            break;
        if(allLinks[i].getStatus() == status)
        {
            links.push_back(allLinks[i]);
            --size;
        }
    }

    return links;
}

// return true if link alrady exist in alllist
bool LinkStore::ContainsLink(const std::string& link)
{
    for (int i = 0; i < allLinks.size(); ++i)
    {
        if (allLinks[i].getUrl() == link)
        {
            return true;
        }
    }
    return false;
}

//return true if all links is loaded
bool LinkStore::Allloaded()
{
    for (const auto& link : allLinks)
    {
        if(link.getStatus() == LinkStatus::WAITING)
            return false;
    }
    return true;
}

//add/upadate new link to "alllinks"
void LinkStore::Save(const Link& link)
{
    for (int i = 0; i < allLinks.size(); ++i)
    {
        if(allLinks[i].getUrl() == link.getUrl())
        {
            allLinks[i] = link;
            return;
        }
    }
    allLinks.push_back(link);
}