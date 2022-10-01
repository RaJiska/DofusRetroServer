#include "ACommand.hpp"

ACommand::ACommand(void)
{
}

ICommand::CommandState ACommand::getCommandState(void) const noexcept
{
	return this->commandState;
}

std::queue<NetworkMessage> &ACommand::getDispatchList(void) noexcept
{
	return this->dispatchList;
}