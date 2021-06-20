#include "DataStore.hpp"

DataStore::DataStore()
{}

Data DataStore::getByTitle(const std::string& title)
{
    return Data();
}

void DataStore::addNewData(Data data)
{
    std::string url = data.getUrl();
    std::string title = data.getTitle();
    std::string allText = data.getAllText();
    std::string description = data.getDescription();

    std::vector<std::string> insertValues = {url, title, allText, description};
    std::vector<std::string> updateValues = {title, allText, description, url};

    std::string updateQuery = "UPDATE Crawler.data2 SET title = ?, allText = ?, description = ? WHERE url =?";

    try
    {
        DBConnector::ExecuteQuery("INSERT INTO Crawler.data2 values (?, ?, ?, ?)", insertValues);
    }
    catch(sql::SQLException& e)
    {
        std::cout << "wtf";
        if(e.getErrorCode() == 1062 || e.getErrorCode() == 1061)
            DBConnector::ExecuteQuery(updateQuery, updateValues);
    }
    
}