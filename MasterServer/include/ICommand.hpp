#pragma once

#include "NetworkMessage.hpp"

class ICommand
{
	public:
	typedef enum CommandState
	{
		WAITING_FOR_INPUT,
		MESSAGES_TO_DISPATCH,
		END
	} CommandState;

	virtual ~ICommand() {}

	virtual void processMessage(const NetworkMessage &message) = 0;
	virtual void processCommand(void) = 0;
	virtual bool commandComplete(void) const noexcept = 0;

	virtual CommandState getCommandState(void) const noexcept = 0;
};