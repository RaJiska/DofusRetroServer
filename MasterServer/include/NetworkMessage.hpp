#pragma once

#include <string>

class NetworkMessage
{
	public:
	typedef enum Target
	{
		PEER,
		BROADCAST,
		NONE
	} Target;

	NetworkMessage();
	NetworkMessage(Target target, const std::string &message, bool process = false);
	NetworkMessage(Target target, const char *message, std::size_t len, bool process = false);
	virtual ~NetworkMessage() = default;

	Target getTarget(void) const noexcept;
	const std::string &getMessage() const noexcept;

	static const std::string ERROR_WRONG_PASS;
	static const std::string ERROR_BANNED;
	static const std::string ERROR_UNFINISHED_CONNECTION;
	static const std::string ERROR_ALREADY_CONNETING;
	static const std::string ERROR_ALREADY_CONNECTED;
	static const std::string ERROR_NEW_VERSION;
	static const std::string ERROR_INVALID_ACCOUNT;
	static const std::string ERROR_ACCOUNT_DISCONNECTED;
	static const std::string ERROR_INVALID_ACCOUNT_TIME;
	static const std::string ERROR_SERVER_FULL;
	static const std::string ERROR_OLD_ACCOUNT;
	static const std::string ERROR_OLD_ACCOUNT_USE_NEW;
	static const std::string ERROR_ACCOUNT_IN_MAINTENANCE;
	static const std::string ERROR_NICKNAME_ALREADY_USED;

	private:
	Target target = Target::NONE;
	std::string message = "";

	void processString(void) noexcept;
};