#include <string>
#include "user.h"
using namespace  std;

// User ///////////////////////////////////////////////////////////////////////
User::User(const string& login, const string& password, const string& name) : 
    _login(login), _password(password), _name(name) { }
void User::setUserPassword(const string& password){
    _password = password;
}
void User::setUserName(const std::string& name){
    _name = name;
}
const string& User::getUserLogin() const{
    return _login;
}
const string& User::getUserPassword(){
    return _password;
}
const string& User::getUserName() const{
    return _name;
}
