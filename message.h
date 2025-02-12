#pragma once
#include <string>

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
