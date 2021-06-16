#include <algorithm>
#include <iostream>
#include "LinkStore.hpp"

LinkStore::LinkStore(){}

std::vector<Link> LinkStore::getAllLinks() const
{
    return allLinks;
}

std::optional<Link> LinkStore::getByUrl(const std::string& url)
{
    for (const auto)
}