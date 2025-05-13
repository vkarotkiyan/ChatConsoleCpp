#pragma once
#include <string>
#include <ctime>

class Message { // Сообщение
public:
	Message(const std::string & text, const std::string& from, const std::string& to, const std::time_t& dateTime);
	~Message() = default;
	const std::string& getText() const;
	const std::string& getFrom() const;
	const std::string& getTo() const;
	const std::time_t& getTime() const;
private:
	std::string _text;
	std::string _from;
	std::string _to;
	std::time_t _dateTime;
};
