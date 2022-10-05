#include "ACommand.hpp"

ACommand::ACommand()
{
}

std::queue<NetworkMessage> ACommand::consumeDispatchList(void)
{
	std::queue<NetworkMessage> dispatchList = this->dispatchList;
	std::queue<NetworkMessage> empty;

	this->dispatchList.swap(empty);
	return dispatchList;
}

void ACommand::processMessage(const NetworkMessage &message)
{
	// Ignore message by default
}

void ACommand::process(void)
{
	// Ignore process by default
}

ICommand::ExitStatus ACommand::getExitStatus(void) const noexcept
{
	return this->exitStatus;
}