#include "ACommand.hpp"

ACommand::ACommand(void)
{
}

ICommand::CommandState ACommand::getCommandState(void) const noexcept
{
	return this->commandState;
}