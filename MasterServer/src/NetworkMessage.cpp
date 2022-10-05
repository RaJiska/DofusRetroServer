#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage()
{
}

NetworkMessage::NetworkMessage(
	NetworkMessage::Target target, const std::string &message, bool process)
	: target(target), message(message)
{
	if (process)
		this->processString();
}

NetworkMessage::NetworkMessage(
	NetworkMessage::Target target, const char *message, std::size_t len, bool process)
	: target(target), message(message, len)
{
	if (process)
		this->processString();
}

NetworkMessage::Target NetworkMessage::getTarget(void) const noexcept
{
	return this->target;
}

const std::string &NetworkMessage::getMessage(void) const noexcept
{
	return this->message;
}

void NetworkMessage::processString(void) noexcept
{
	auto sz = this->message.size();

	if (this->message.find("\n", sz - 1) != std::string::npos)
		this->message.erase(sz - 1);
}

const std::string NetworkMessage::ERROR_WRONG_PASS = "AlEf";
const std::string NetworkMessage::ERROR_BANNED = "AlEb";
const std::string NetworkMessage::ERROR_UNFINISHED_CONNECTION = "AlEn";
const std::string NetworkMessage::ERROR_ALREADY_CONNETING = "AlEa";
const std::string NetworkMessage::ERROR_ALREADY_CONNECTED = "AlEc";
const std::string NetworkMessage::ERROR_NEW_VERSION = "AlEv"; // + version
const std::string NetworkMessage::ERROR_INVALID_ACCOUNT = "AlEp";
const std::string NetworkMessage::ERROR_ACCOUNT_DISCONNECTED = "AlEd";
const std::string NetworkMessage::ERROR_INVALID_ACCOUNT_TIME = "AlEl"; // + days | hours | minutes
const std::string NetworkMessage::ERROR_SERVER_FULL = "AlEw";
const std::string NetworkMessage::ERROR_OLD_ACCOUNT = "AlEo";
const std::string NetworkMessage::ERROR_OLD_ACCOUNT_USE_NEW = "AlEe";
const std::string NetworkMessage::ERROR_ACCOUNT_IN_MAINTENANCE = "AlEm";
const std::string NetworkMessage::ERROR_NICKNAME_ALREADY_USED = "AlEs";