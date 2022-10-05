#pragma once

#include "NetworkMessage.hpp"
#include "Exceptions/CommandException.hpp"

#include <queue>

class ICommand
{
	public:
	typedef enum ExitStatus {
		OK,
		ERROR,
	} ExitStatus;

	virtual ~ICommand() {}

	virtual void processMessage(const NetworkMessage &message) = 0;
	virtual void process(void) = 0;
	virtual std::queue<NetworkMessage> consumeDispatchList(void) = 0;
	virtual bool isOver() const noexcept = 0;

	virtual ExitStatus getExitStatus(void) const noexcept = 0;
};