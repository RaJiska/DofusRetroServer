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

	Target getTarget(void) const noexcept;
	const std::string &getMessage() const noexcept;

	private:
	Target target;
	const std::string &message;
};