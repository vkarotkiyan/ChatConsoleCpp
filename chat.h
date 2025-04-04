#pragma once
#include <string>
#include <vector>
#include <memory>
#include "user.h"
#include "message.h"

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
//	std::vector<User> _users;
	std::vector<std::shared_ptr<User>> _users; // Массив пользователей // Исправлено по рекомендации проверяющего
	std::vector<Message> _messages; // Массив сообщений
	std::shared_ptr<User> _currentUser = nullptr; // Активный пользователь
	std::shared_ptr<User> _userForChat = nullptr; // Пользователь, с которым ведется общение
};
