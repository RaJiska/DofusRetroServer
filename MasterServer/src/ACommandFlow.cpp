#include "ACommandFlow.hpp"

ACommandFlow::ACommandFlow()
{
}

std::queue<NetworkMessage> ACommandFlow::process(void)
{
	// Only return if the command is complete
	std::queue<NetworkMessage> msgs;

	if (!this->currentCommand->isOver())
		return msgs;
	this->currentCommand->process();
	this->state = this->state + 1;
	msgs = this->currentCommand->consumeDispatchList();
	if (!this->isFlowOver())
		this->currentCommand = std::move(this->commandMap[this->state]());
	return msgs;
}