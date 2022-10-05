#include <iostream>

class CommandFlowException : public std::exception
{
	public:
	CommandFlowException(const char *msg) : msg(msg) {}

	const char *what() const throw() {
		return msg;
	}

	private:
	const char *msg;
};