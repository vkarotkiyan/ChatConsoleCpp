#pragma once
#include <exception>
#include <cstdlib>
#include <locale>
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#endif
constexpr auto U_FILE = "users.txt";
constexpr auto M_FILE = "messages.txt";

// Настройка консоли для Windows и Linux
static void set_cons() {
#if defined(_WIN64) || defined(_WIN32)
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//_setmode(_fileno(stdin), _O_U16TEXT);
#else
	setlocale(LC_ALL, "");
#endif
}
// Очистка экрана консоли
static void clear_screen() {
#if defined(_WIN64) || defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}
// Файл с путем 
static std::string pathFile(const char* file) {
	#if defined(_WIN64) || defined(_WIN32)
		std::string str1 = getenv("HOMEDRIVE");
		std::string str2 = getenv("HOMEPATH");
		return str1 + str2 + "\\" + (std::string)file;
	#else
		return getenv("HOME") + (std::string)"/" + (std::string)file;
	#endif
	}

// Exceptions /////////////////////////////////////////////////////////////////
class UserLoginExc : public std::exception {
public:
	virtual const char* what() const noexcept override {
		clear_screen();
		return "Ошибка: такой логин уже существует.\n";
	};
};

class UserNameExc : public std::exception {
public:
	virtual const char* what() const noexcept override {
		clear_screen();
		return "Ошибка: такое имя уже существует.\n";
	};
};
