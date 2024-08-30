#include "user.h"

User::User(const std::string& name, const std::string& surname, const std::string& email, int age, int belance)
:_name(name),_surname(surname),_username(username),_password(password),_email(email),_age(age),_amount(belance){

}

User::getName() const{
    return _name;
}

User::getSurname() const{
    return _surname;
}

User::getAge() const{
    return _age;
}

User::getEmail() const{
    return _email;
}

User::getUsername() const{
    return _username;
}

User::getPassword() const {
    return _password;
}

User::getBelance()const{
    return _belance;
}

User::setBelance(int newBelance){
    _belance = newBelance;
}

User::setAge(int newage){
    _age = age;
}

User::setName(std::string newname){
    _name = newname;
}

User::setSurname(std::string newsurname){
    _surname = newsurname;
}

User::setEmail(std::string newemail){
    _email = newemail;
}

User::setUsername(std::string newusername){
    _username = newusername;
}

User::setPassword(std::string newpassword){
    _password = newpassword;
}
    