#include <iostream>
#include <algorithm>
#include <vector>
#include <nuspell/dictionary.hxx>
#include <nuspell/finder.hxx>

#include "SpellCorrector/SpellCorrector.hpp"
#include "DBConnector/DBConnector.hpp"

std::vector<std::string> Split (const std::string& query, char separator)
{
    std::vector<std::string> words;
    int from = 0, to = 0;
    while((to = query.find(separator, to)) != std::string::npos)
    {
        ++to;
        words.push_back(query.substr(from, to - from - 1));
        from = to;
    }
    words.push_back(query.substr(from, query.size() - from));
    return words;
}

int main()
{
    DBConnector::Initialize("tcp://127.0.0.1:3306", "root", "erebuni11");
    SpellCorrector coorector;
    coorector.Init();

    std::string query;
    std::getline(std::cin, query);
    std::vector<std::string> allWords = Split(query, ' ');

    std::vector<std::vector<std::string>> suggestions (allWords.size());
    if(coorector.CheckQuery(allWords, suggestions))
    {
        sql::ResultSet* resultSet = DBConnector::ExecuteQuery("SELECT * FROM Crawler.data2 WHERE title LIKE '%" + query + "%'");
    
        while(resultSet->next())
        {       
            std::string url = resultSet->getString("url");
            
            std::cout << std::endl <<  url;
        }
    }
    else
    {
        for(int i = 0; i < allWords.size(); ++i)
        {
            std::cout << "Suggestions for \"" << allWords[i] << "\" :" << "\n";
            for(int j = 0; j < suggestions[i].size(); ++j)
                std::cout << suggestions[i][j] << "\n";

        }
    }

}