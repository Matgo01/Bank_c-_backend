#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "service.h"
#include "database.h"
#include "crow_all.h"

class Controller{
    public:
      Controller(Service& service, Database& database);

      void addRoutes(crow::SimpleApp& app);

    private:
       Service& _service;
       Database& _database;

};

#endif