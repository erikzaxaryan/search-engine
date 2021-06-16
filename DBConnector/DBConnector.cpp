#include "DBConnector.hpp"


sql::Connection* DBConnector::connection;
sql::Statement* DBConnector::statement;
sql::PreparedStatement* DBConnector::preparedStatement;


void DBConnector::Initialize(const std::string& host, const std::string& user, const std::string& password)
{
    sql::Driver* driver = get_driver_instance();
    sql::Connection* con = driver->connect(host, user, password);
    con->setSchema("Crawler");

    DBConnector::connection = con;
    DBConnector::statement = con->createStatement();
}



sql::ResultSet* DBConnector::ExecuteQuery(const std::string& query)
{
    return DBConnector::statement->executeQuery(query);
}

sql::ResultSet* DBConnector::ExecuteQuery(const std::string& query, std::vector<std::string>& values)
{
    DBConnector::preparedStatement = DBConnector::connection->prepareStatement(query);

    for (int i = 0; i < values.size(); i++)
    {
        DBConnector::preparedStatement->setString(i + 1, values[i]);
    }
    
    return DBConnector::preparedStatement->executeQuery();

}