#include "controller.h"

Controller::Controller(Service& service,Database& database):_service(service),_database(database){

}

void Controller::addRoutes(crow::SimepleApp& app){
    CROW_ROUTE(app, "/user/create").methods(crow::HTTPMethod::Post)([this](const crow::request& req){
        crow::response res;
        service.createUser(req, res);
        return res;
    
     });

    CROW_ROUTE(app, "/user/<int>").methods(crow::HTTPMethod::Get)([this](const crow::request& req, int userId) {
        crow::response res;
        service.getUser(req, res);
        return res;
    });

    CROW_ROUTE(app, "/user/update/<int>").methods(crow::HTTPMethod::Put)([this](const crow::request& req, int userId) {
        crow::response res;
        service.updateUser(req, res);
        return res;
    });

    CROW_ROUTE(app, "/user/delete/<int>").methods(crow::HTTPMethod::Delete)([this](const crow::request& req, int userId) {
        crow::response res;
        service.deleteUser(req, res);
        return res;
    });

    CROW_ROUTE(app, "/user/login").methods(crow::HTTPMethod::Get)([this](const crow::request& req, const std::string& username, const std::string& password)){
        crow::response res;
        service.login(req, res);
        return res;
    }

    }