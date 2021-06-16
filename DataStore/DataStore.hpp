#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../DBConnector/DBConnector.hpp"
#include "Data.hpp"


class DataStore
{
    
public:
    //Def constructor
    DataStore();


    //Get data by Title
    Data getByTitle(const std::string& title);


    //Add new Data
    void addNewData(Data data);
};