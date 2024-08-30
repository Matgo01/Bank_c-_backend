#include "service.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

Service::Service(Database& database):db(database){

}

void Service::createUser(const crow::requst& req, crow::response& res){
    try{
    auto json = crow::json::load(req.body);
    if(!json){
        res.code = 400;
        res.write("incalid json");
        return;
    }
    std::string name = json["name"].s();
    std::string username = json["surname"].s();
    std::string username = json["username"].s();
    std::string password = json["password"].s();
    std::string email = json["email"].s();
    int age = json["age"].s();

    std::string query = "INSERT INTO users (name, surname,username,password,email,age) VALUES (?,?,?,?,?,?)";
    auto result = db.executeQuery(query);

    if(result){
        res.code = 201;
        res.write("USer created");
    }else{
        res.code = 500;
        res.write("database error");
    }
    } catch(const std::exception& e){
        res.code = 500;
        res.write(e.what());
    }
}

void Service::getUser(const crow::request& req, crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        std::string query = "SELECT name, surname, username, password, email, age FROM users WHERE id = "+std::to_string(userId);
        auto result = db.executeQuery(query);

        crow::json::value response;
        if(result && result->next()){
            response["name"] = result->getString("name");
            response["surname"] = result->getString("surname");
            response["username"] = result->getString("username");
            response["password"] = result->getString("password");
            response["email"] = result->getString("email");
            response["age"] = result->getInt("age");
        }else{
            res.code = 404;
            res.write("User not found");
            return;
        }
        res.code = 200;
        res.write(response.dump());
    }catch(sql::Exception& e){
        res.code = 500;
        res.write(std::strign(e.what()));
    }
}

void Service::updateUser(const crow::request& req, crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        auto json = crow::json::load(req.body);
        if(!json){
            res.code = 400;
            res.write("invalid json");
            return;
        }

        std::string name = json["name"].s();
        std::string surname = json["surname"].s(); 
        std::string username = username["username"].s();
        std::string password = password["password"].s();
        std::string email = json["email"].s();
        int age = json["age"].i();

       
    }
}

void Service::deleteUser(const crow::request& req, const crow::response& res){
    try{
        int userId = std::stoi(req.url_params.get("userId"));
        std::string query = "DELETE FROM users WHERE id = "+std::to_string(userId);
        auto result = db.executeQuery(query);
        
        if(result){
            res.code = 204;
            res.write("User deleted");
        }else{
            res.code = 404;
            res.write("User not found");
        }
    }catch(sql::Exception& e){
        res.code = 500;
        res.write("Database error:"+std::string(e.what()));
    }
}

bool Service::login(const crow::request& req, const crow::response& res){
    try{
        std::string username= std::stoi(req.url_params.get("username"));
        std::string password = std::stoi(req.url_params.get("password"));
        std::string query = "SELECT id FROM users WHERE username = '"+username+"' AND password = '"+password+"'";
        auto result = db.executeQuery(query);
        if(result){
            res.code = 204;
            res.write("User logged in");
            return true;
        }else{
            res.code = 401;
            res.write("Invalid credentials");
            return false;
        }
    }catch(sql::Exception& e){
        res.code = 500;
        res.write("Database error:"+std::string(e.what()));
        return false;
    }
}

void Service::deposit(const crow::request% req, const crow::response& res ){

    try{    
    int userId = std::stoi(req.url_params.get("userId"));
    auto json = crow::json::load(req.body);

    if(!json){
        res.code = 400;
        res.write("Invalid JSON");
        return;
    }

    double amount = json["amount"].d();

    if(amount <=0){
        res.code = 400;
        res.write("invalid deposit amount");
        return;
    }

    std::string query = "UPDATE users SET balance = balance + ? WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(db.getConnection()->prepareStatement(query));
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, userId);

        int rowsAffected = pstmt->executeUpdate();

         if (rowsAffected > 0) {
            res.code = 200;
            res.write("Deposit successful");
        } else {
            res.code = 404;
            res.write("User not found");
        }

    }catch (const sql::SQLException& e) {
        res.code = 500;
        res.write("Database error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        res.code = 500;
        res.write("Error: " + std::string(e.what()));
    }


}

void Service::withdraw(const crow::request& req, crow::response& res){
    try {
        int userId = std::stoi(req.url_params.get("userId"));
        auto json = crow::json::load(req.body);

        if (!json) {
            res.code = 400;
            res.write("Invalid JSON");
            return;
        }

        double amount = json["amount"].d();

        if (amount <= 0) {
            res.code = 400;
            res.write("Invalid withdrawal amount");
            return;
        }

        std::string selectQuery = "SELECT balance FROM users WHERE id = ?";
        std::unique_ptr<sql::PreparedStatement> pstmtSelect(db.getConnection()->prepareStatement(selectQuery));
        pstmtSelect->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> rs(pstmtSelect->executeQuery());

        if (rs->next()) {
            double currentBalance = rs->getDouble("balance");

            if (currentBalance < amount) {
                res.code = 400;
                res.write("Insufficient funds");
                return;
            }

            std::string updateQuery = "UPDATE users SET balance = balance - ? WHERE id = ?";
            std::unique_ptr<sql::PreparedStatement> pstmtUpdate(db.getConnection()->prepareStatement(updateQuery));
            pstmtUpdate->setDouble(1, amount);
            pstmtUpdate->setInt(2, userId);

            int rowsAffected = pstmtUpdate->executeUpdate();

            if (rowsAffected > 0) {
                res.code = 200;
                res.write("Withdrawal successful");
            } else {
                res.code = 404;
                res.write("User not found");
            }
        } else {
            res.code = 404;
            res.write("User not found");
        }
    } catch (const sql::SQLException& e) {
        res.code = 500;
        res.write("Database error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        res.code = 500;
        res.write("Error: " + std::string(e.what()));
    }

}