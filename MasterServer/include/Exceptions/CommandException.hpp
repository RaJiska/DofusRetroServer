#include <iostream>

class CommandException : public std::exception
{
	public:
	CommandException(const char *msg) : msg(msg) {}

	const char *what() const throw() {
		return msg;
	}

	private:
	const char *msg;
};