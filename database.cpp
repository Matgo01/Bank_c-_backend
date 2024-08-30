#include "database.h"

Database::Database(const std::string& db_host, const std::string& db_user, const std::string& password, const std::string db_database):
db_host(db_host), db_user(db_user), password(password), db_database(db_database){

}

Database::~Database() {
   
}

bool Database::connect(){
    try{
        conn = std::unique_ptr<sql::Connection(driver->connect(host,user,password));

        conn->setSchema(database);
        return true;
    }catch(sql::Exception &e){
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
        return false;
    }
}

std::unique_ptr<sql::ResultSet> Database::executeQuery(const std::string& query){
    try{
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
        return std::move(res);
    }catch(sql::Exception &e){
        std::cerr << "Error executing query: " << e.what() << std::endl;
        return nullptr;
    }
}