#pragma once
#include <string>
#include <vector>

class User { // Пользователь
public:
	User(const std::string&, const std::string&, const std::string&);
	~User() = default;
	void setUserPassword(const std::string&);
	void setUserName(const std::string&);
	const std::string& getUserLogin() const;
	const std::string& getUserPassword();
	const std::string& getUserName() const;
private:
	std::string _login;
	std::string _password;
	std::string _name;
};
