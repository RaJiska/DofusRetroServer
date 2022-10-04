#include "Commands/Version.hpp"

Command::Version::Version(void) : ACommand()
{
	NetworkMessage msg(NetworkMessage::Target::PEER, "HCaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	this->pushMessagetoDispatchList(msg);
}

void Command::Version::processMessage(const NetworkMessage &message)
{
}

ICommand::CommandState Command::Version::adjustStepAfterDispatch(void)
{
	this->commandState = ICommand::CommandState::END;
	return this->commandState;
}
