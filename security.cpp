#include "security.h"
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <iostream>
#include <stdexcept>

static const std::string SECRET_KEY = "secret_key";

std::string Security::hashPassword(const std::string& password){
    unsigned char salt[16];
    RAND_bytes(salt, sizeof(salt));

    unsigned char hash[32];
    PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.size(),salt, sizeof(salt),10000, sizeof(hash),hash);

    return std::string(reinterpret_cast<char*>(hash),sizeof(hash));
}

bool Security::verifyPassword(const std::string& hashedPassword, const std::string& password) {
    std::string hashAttempt = hashPassword(password);
    return hashAttempt == hashedPassword;
}

std::string Security::generateJWT(const std::string& userId, Role role){
    auto token = jwt::create()
    .set_issuer("banking-app")
    .set_type("JWT")
    .set_payload_claim("userId",jwt::claim(userId))
    .set_payload_claim("role",jwt::claim(std::to_string(static_cast<int>(role))))
    .sign(jwt::algorithm::hs256{SECRET_KEY});

    return token;
}

bool Security::verifyJWT(const std::string& token, std::string& userId, Role& role){
    try{
        auto decode = jwt::decode(token);
        auto verifier = jwr::verify().allow_algorithm(jwt::algorithm::hs256{SECRET_KEY});
        verifier.verify(decode);

        userId = decode.get_payload_claim("userId").as_string();
        role = static_cast<Role>(std::stoi(decode.get_payload_claim("role").as_string()));

        return true;
    }catch (const std::exception& e) {
        std::cerr << "JWT verification failed: " << e.what() << std::endl;
        return false;
    }

}

bool Security::authorizeUser(Role userRole, Role requiredRole) {
    return userRole >= requiredRole;
}