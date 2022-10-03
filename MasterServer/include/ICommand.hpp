#pragma once

#include "NetworkMessage.hpp"
#include "Exceptions/CommandException.hpp"

#include <queue>

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
	virtual CommandState advanceStep(void) = 0;

	virtual CommandState getCommandState(void) const noexcept = 0;
	virtual std::queue<NetworkMessage> &getDispatchList(void) noexcept = 0;
};