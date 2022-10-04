#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage(
	NetworkMessage::Target target, const std::string &message)
	: target(target), message(message)
{
}

NetworkMessage::NetworkMessage(
	NetworkMessage::Target target, const char *message, std::size_t len)
	: target(target), message(message, len)
{
}

NetworkMessage::Target NetworkMessage::getTarget(void) const noexcept
{
	return this->target;
}

const std::string &NetworkMessage::getMessage(void) const noexcept
{
	return this->message;
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