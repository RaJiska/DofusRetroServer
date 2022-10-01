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

void Command::Version::processCommand(void) noexcept
{

}

bool Command::Version::commandComplete(void) const noexcept
{
	return true; // TODO: Placeholder
	//return this->state == Command::Version::MessageState::END;
}

void Command::Version::setNextStep(void) noexcept
{
	this->commandState = ICommand::CommandState::END;
}