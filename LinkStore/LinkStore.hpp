#ifndef LINKSTORE_HPP
#define LINKSTORE_HPP

#include <optional>
#include <vector>

#include "Link.hpp"

class LinkStore
{
private:
    std::vector<Link> allLinks;
public:
    LinkStore();

    std::optional<Link> getByUrl(const std::string& url);
    std::vector<Link> getBy(const std::string& domain, LinkStatus status, std::size_t size);

    //Add new link
    void Save(const Link& link);


    
    bool ContainsLink(const std::string& link);

    //Check all links loaded
    bool Allloaded();

    //Get all links
    std::vector<Link> getAllLinks() const;
};

#endif