#ifndef DATABASE_H
#define DATABASE_H

#include "crow_all.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/ exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <memory>

class Database{
    private:
       sql::mysql::MySQL_Driver *driver;
       std::unique_ptr<sql::Connection> conn;
       std::unique_ptr<sql::ResultSet> res;
       std::unique_ptr<sql::Statement> stmt;

       std::string host;
       std::string user;
       std::string password;
       std::string database;

    public:
       Database(const std::string& db_host, const std::string& db_user, const std::string& db_password, const std::string& db_database);
       ~Database();
       bool connect();
       std::unique_ptr<sql::ResultSet> executeQuery(const std::string& query);

};

#endif