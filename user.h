#ifndef USER_H
#define USER_H

#include <string>



class User{
    public:
      public:
    // Constructor declaration
    User(const std::string& name, const std::string& surname, const std::string& username, const std::string& password,const std::string& email, int age, int belance);

    // Getter methods
    std::string getName() const;
    std::string getSurname() const;
    std::string getEmail() const;

    std::string getPassword() const;

    std::string getUsername() const;
    int getAge() const;

    int getBelance() const;

    // Setter methods
    void setName(const std::string& name);
    void setSurname(const std::string& surname);
    void setEmail(const std::string& email);
    void setAge(int age);

    void setPassword(const std::string& password);

    void setUsername(const std::string& username);

    void setBelance(const int newBelance);



    private:
       std::string _name;
       std::string _surname;
       std::string _username;
       std::string _password;
       std::string _email;
       int _age;
       int _belance;
       

};

#endif