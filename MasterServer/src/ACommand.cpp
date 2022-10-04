#include "ACommand.hpp"

ACommand::ACommand(void)
{
}

std::queue<NetworkMessage> ACommand::consumeDispatchList(void)
{
	if (this->commandState != ICommand::CommandState::MESSAGES_TO_DISPATCH) {
		throw CommandException("Command not in a state to dispatch messages");
	}

	// TODO: Optimise
	std::queue<NetworkMessage> dispatchList = this->dispatchList;
	std::queue<NetworkMessage> empty;

	this->dispatchList.swap(empty);
	this->adjustStepAfterDispatch();
	return dispatchList;
}

ICommand::CommandState ACommand::getCommandState(void) const noexcept
{
	return this->commandState;
}

ICommand::ExitStatus ACommand::getExitStatus(void) const noexcept
{
	return this->exitStatus;
}

void ACommand::pushMessagetoDispatchList(const NetworkMessage &message, DispatchFlag flag)
{
	this->dispatchFlag = flag;
	this->dispatchList.push(message); // TODO: Optimise
	this->commandState = ICommand::CommandState::MESSAGES_TO_DISPATCH;
}

ICommand::CommandState ACommand::handleEnd(const NetworkMessage &msg) const
{
	throw CommandException("Command already ended, nothing to do");
}