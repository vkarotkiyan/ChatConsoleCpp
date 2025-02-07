#pragma once
#include <string>
#include <vector>
#include <memory>

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

class Message { // Сообщение
public:
	Message(const std::string&, const std::string&, const std::string&);
	~Message() = default;
	const std::string& getText() const;
	const std::string& getFrom() const;
	const std::string& getTo() const;
private:
	std::string _text;
	std::string _from;
	std::string _to;
};

class Chat {
public:
	Chat();
	~Chat() = default;
	bool isWork() const;
	void initMenu(); // Начальное меню
	void login(); // Аутентификация пользователя
	void signUp(); // Регистрация пользователя
	void showUserList() const; // Отображение списка пользователей
	void userMenu(); // Меню авторизованного пользователя
	std::shared_ptr<User> getUserByLogin(const std::string&) const;
	std::shared_ptr<User> getUserByName(const std::string&) const;
	std::shared_ptr<User> getCurrentUser() const;
	std::shared_ptr<User> getUserForChat() const;
	void setUserForChat(); // Выбор пользователя для общения
	void addMessage(); // Ввод сообщения
	void showChat() const; // Отображение списка сообщений
private:
	bool _isWork = false;
	std::vector<User> _users; // Массив пользователей
	std::vector<Message> _messages; // Массив сообщений
	std::shared_ptr<User> _currentUser = nullptr; // Активный пользователь
	std::shared_ptr<User> _userForChat = nullptr; // Пользователь, с которым ведется общение
};
