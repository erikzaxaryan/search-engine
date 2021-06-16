#ifndef DBCONNECTOR_HPP
#define DBCONNECTOR_HPP

#include <vector>
#include <iostream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DBConnector
{
public:
    static sql::Connection* connection;
    static sql::Statement* statement;
    static sql::PreparedStatement* preparedStatement;


    static void Initialize(const std::string& host, const std::string& user, const std::string& password);

    static sql::ResultSet* ExecuteQuery(const std::string& query);

    static  sql::ResultSet* ExecuteQuery(const std::string& query, std::vector<std::string>& values);


};


#endif