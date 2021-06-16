#ifndef WEBSITESTORE_HPP
#define WEBSITESTORE_HPP

#include<vector>
#include<unordered_map>


#include "../DBConnector/DBConnector.hpp"
#include"Website.hpp"

class WebsiteStore {
private:
std::unordered_map<std::string, Website> allWebs;

public:

    WebsiteStore();

    std::vector<Website> getAll() const;


    void add(const Website& website);

    void update(const Website& website);
};

#endif