#pragma once
#include <string>
#include <stdexcept>
class EventException : public std::exception
{
private:
	std::string message;
public:
	explicit EventException(const std::string& message) : message(message) {}
	const char* what() const noexcept override
	{
		return message.c_str();
	}
};

