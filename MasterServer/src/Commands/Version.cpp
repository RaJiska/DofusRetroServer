#include "Commands/Version.hpp"

Command::Version::Version(void) : ACommand()
{
	NetworkMessage msg(NetworkMessage::Target::PEER, "HCaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	this->dispatchList.push(msg); // TODO: Optimise
	this->commandState = ICommand::CommandState::MESSAGES_TO_DISPATCH;
}

void Command::Version::processMessage(const NetworkMessage &message)
{
	
}

ICommand::CommandState Command::Version::advanceStep(void) noexcept
{
	this->commandState = ICommand::CommandState::END;
	return this->commandState;
}

void Command::Version::setNextStep(void) noexcept
{
	this->commandState = ICommand::CommandState::END;
}