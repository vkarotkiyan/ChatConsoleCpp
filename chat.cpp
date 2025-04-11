#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "chat.h"
#include "misc.h"
namespace fs = std::filesystem;
using namespace  std;

// Отображение времени в нужном формате
static const string showTime(const time_t& time) {
	struct tm* timeinfo;
	char buffer[80];
	timeinfo = localtime(&time);
	strftime(buffer, 80, "%d.%m.%Y %H:%M", timeinfo);
	return string(buffer);
}

// Chat ///////////////////////////////////////////////////////////////////////
Chat::Chat() { _isWork = true; }

bool Chat::isWork() const { return _isWork; }

void Chat::initMenu() {
	char oper = '0';
	do {
		if (!_currentUser) {
			showUserList();
			cout << "Регистрация (1) | Вход в чат (2) | Завершение работы (0)" << endl;
			cin >> oper;
		}
		switch (oper) {
		case '1':
			try {
				signUp();
			}
			catch (const exception& e) {
				cout << e.what() << endl;
			}
			break;
		case '2':
			login();
			userMenu();
			break;
		case '0':
			_isWork = false;
			break;
		default:
			clear_screen();
			cout << "Ошибка ввода. Введите 1, 2 или 0" << endl;
			break;
		}
	} while (_isWork);
}

void Chat::login() {
	string login, password;
	char oper;
	clear_screen();
	do {
		cout << "Логин: ";
		cin >> login;
		cout << "Пароль: ";
		cin >> password;
		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr || (password != _currentUser->getUserPassword())) {
			_currentUser = nullptr;
			cout << "Ошибка входа." << endl;
			cout << "Нажмите '0' для выхода в меню или любую клавишу для повтора: ";
			cin >> oper;
			if (oper == '0')
				break;
		}
	} while (!_currentUser);
	clear_screen();
}

void Chat::signUp() { // Регистрация пользователя
	string login, password, name;
	clear_screen();
	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";
	cin >> password;
	cout << "Имя: ";
	cin >> name;
	if (getUserByLogin(login) || login == "all") {
		throw UserLoginExc();
	}
	if (getUserByName(name) || name == "all") {
		throw UserNameExc();
	}
//	User user = User(login, password, name);
	shared_ptr<User> user(new User(login, password, name)); // Исправлено по рекомендации проверяющего
	_users.push_back(user);
	clear_screen();
}

void Chat::showUserList() const {
	cout << "----------------- Список пользователей -----------------" << endl;
	for (auto& user : _users) {
		cout << user->getUserName() << " (" << user->getUserLogin() << ")";
		if (_currentUser)
			if (_currentUser->getUserLogin() == user->getUserLogin())
				cout << " (активный пользователь)";
		cout << endl;
	}
	cout << "--------------------------------------------------------" << std::endl;
}

void Chat::userMenu() {
	char oper;
	while (_currentUser) {
		showUserList();
		if (!_userForChat)
			cout << "Выбрать пользователя для общения (1)";
		else
			cout << "В общий чат (1) | Поменять собеседника (3)";
		cout << " | Добавить сообщение (2) | Выход из чата (0)" << endl;
		showChat();
		cin >> oper;
		switch (oper) {
		case '1':
			clear_screen(); 
			if (!_userForChat) setUserForChat();
			else _userForChat = nullptr;
			break;
		case '2':
			clear_screen();
			showUserList();
			if (!_userForChat)
				cout << "Выбрать пользователя для общения (1)";
			else
				cout << "Перейти в общий чат (1) | Сменить собеседника (3)";
			cout << " | Добавить сообщение (2) | Выход из чата (0)" << endl;
			showChat();
			addMessage();
			break;
		case '3':
			setUserForChat();
			break;
		case '0':
			clear_screen();
			_userForChat = nullptr;
			_currentUser = nullptr;
			break;
		default:
			clear_screen();
			cout << "Ошибка ввода. Введите 1, 2, 3 или 0" << endl;
			break;
		}
	}
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const {
	for (auto& user : _users) {
		if (login == user->getUserLogin()) return user;
	}
	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const {
	for (auto& user : _users) {
		if (name == user->getUserName()) return user;
	}
	return nullptr;
}

shared_ptr<User> Chat::getCurrentUser() const {
	return _currentUser;
}

shared_ptr<User> Chat::getUserForChat() const
{
	return _userForChat;
}

void Chat::setUserForChat() {
	string to;
	clear_screen();
	cout << "Введите имя собеседника: ";
	cin >> to;
	if (!getUserByName(to)) {
		cout << "Ошибка: пользователя с именем " << to << " не существует." << endl;
		return;
	}
	else _userForChat = getUserByName(to);
}

void Chat::addMessage() {
	string text;
	cout << ">> ";
	//cin.ignore();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Исправлено по рекомендации проверяющего
	getline(cin, text);
	if (!_userForChat)
		_messages.push_back(Message{ text, _currentUser->getUserLogin(), "all", time(0) });
	else
		_messages.push_back(Message{ text, _currentUser->getUserLogin(), _userForChat->getUserLogin(), time(0) });
	clear_screen();
}

void Chat::showChat() const { // Вывод списка сообщений. Сообщения активного пользователя выводятся с отступом.
	if (!_userForChat)
		cout << "----------------------------- Общий чат -----------------------------------" << endl;
	else
		cout << "------------------------- Чат с пользователем " << _userForChat->getUserName() << " ------------------------" << endl;
	for (auto& mess : _messages) {
		if (!_userForChat) {
			if (mess.getTo() == "all") {
				if (mess.getFrom() == _currentUser->getUserLogin())	cout << "          ";
				cout << showTime(mess.getTime()) << " " << getUserByLogin(mess.getFrom())->getUserName()
					 << ": " << mess.getText() << endl;
			}
		}
		else {
			if ((mess.getFrom() == _currentUser->getUserLogin() && mess.getTo() == _userForChat->getUserLogin()) ||
				(mess.getFrom() == _userForChat->getUserLogin() && mess.getTo() == _currentUser->getUserLogin()))
			{
				if (_currentUser->getUserLogin() == mess.getFrom()) cout << "          ";
				cout << showTime(mess.getTime()) << " " << getUserByLogin(mess.getFrom())->getUserName()
					 << ": " << mess.getText() << endl;
			}
		}
	}
	cout << "---------------------------------------------------------------------------" << endl;
}

void Chat::writeChat() {
	fstream user_file_wr = fstream(pathFile(U_FILE), ios::out); // Записываем пользователей в файл
	if (!user_file_wr)
		user_file_wr = fstream(pathFile(U_FILE), ios::out | ios::trunc);
	if (user_file_wr) {
		fs::permissions(pathFile(U_FILE), fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
		for (auto& user : _users)
			user_file_wr << user->getUserLogin() << "::" << user->getUserPassword() << "::" << user->getUserName() << endl;
	}
	user_file_wr.close();
	
	fstream message_file_wr = fstream(pathFile(M_FILE), ios::out); // Записываем сообщения в файл
	if (!message_file_wr)
		message_file_wr = fstream(pathFile(M_FILE), ios::out | ios::trunc);
	if (message_file_wr) {
		fs::permissions(pathFile(M_FILE), fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
		for (auto& mess : _messages)
			message_file_wr << mess.getTime() << "::" << mess.getFrom() << "::"	<< mess.getTo() << "::"	<< mess.getText() << endl;
	}
	message_file_wr.close();
}

void Chat::readChat() {
	fstream user_file_r = fstream(pathFile(U_FILE), ios::in); // Заполняем пользователей
	if (user_file_r.is_open()) {
		const string delimiter = "::";
		string str, login, password, name;
		while (getline(user_file_r, str)) {
			size_t end = str.find(delimiter);
			login = str.substr(0, end);
			str.erase(str.begin(), str.begin() + end + 2);
			end = str.find(delimiter);
			password = str.substr(0, end);
			name = str.substr(end + 2);
			shared_ptr<User> user(new User(login, password, name));
			_users.push_back(user);
		}
	}
	user_file_r.close();

	fstream message_file_r = fstream(pathFile(M_FILE), ios::in); // Заполняем сообщения
	if (message_file_r.is_open()) {
		const string delimiter = "::";
		string str, from, to, text;
		time_t time;
		while (getline(message_file_r, str)) {
			size_t end = str.find(delimiter);
			time = stoll(str.substr(0, end));
			str.erase(str.begin(), str.begin() + end + 2);
			end = str.find(delimiter);
			from = str.substr(0, end);
			str.erase(str.begin(), str.begin() + end + 2);
			end = str.find(delimiter);
			to = str.substr(0, end);
			text = str.substr(end + 2);
			_messages.push_back(Message{ text, from, to, time });
		}
	}
	message_file_r.close();
}
