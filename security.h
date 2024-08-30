#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <vector>
#include <opnessl/evp.h>
#include <jwt-cpp/jwt.h>

enum class Role{
    USER,
    ADMIN
};

class Security{
    public:
      static std::string hashPassword(const std::string& password);

      static bool verifyPassword(const std::strin& hashedPassword, const std::string& password);

      static std::string generateJWT(const std::string& userId, Role role);

      static bool verifyJWT(const std::string& token, std::string& userId, Role& role);

      static bool authorizeUser(Role userRole, Role requiredRole);

    
}:

#endif // SECURITY_H