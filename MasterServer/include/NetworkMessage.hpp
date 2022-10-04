#pragma once

#include <string>

class NetworkMessage
{
	public:
	typedef enum Target
	{
		PEER,
		BROADCAST
	} Target;

	NetworkMessage(Target target, const std::string &message);
	NetworkMessage(Target target, const char *message, std::size_t len);
	virtual ~NetworkMessage() = default;

	Target getTarget(void) const noexcept;
	const std::string &getMessage() const noexcept;

	private:
	Target target;
	const std::string message;
};