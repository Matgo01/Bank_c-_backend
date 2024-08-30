#ifndef SERVICE_H
#define SERVICE_H

#include "crow_all.h"
#include "user.h"
#include <string>
#include <memory>
#include "database.h"

class Service{
    private:
      Database& db;
    
    public:
      Service(Database& database);

      void createUser(const crow::request& req, crow::response& res);
      void getUser(const crow::request& req, crow::response& res);
      void updateUser(const crow::request& req, crow::response& res);
      void deleteUser(const crow::request& req, crow::response& res);

      bool login(const crow::request& req, crow::response& res);

      void deposit(const crow::request& req, crow::response& res);

      void withdraw(const crow::request& req, crow::response& res);

};

#endif