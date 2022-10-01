#include "NetworkMessage.hpp"

NetworkMessage::NetworkMessage(
	NetworkMessage::Target target, const std::string &message)
	: target(target), message(message)
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