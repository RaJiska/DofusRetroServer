#pragma once

#include <queue>

#include "NetworkMessage.hpp"

class ICommandFlow
{
	public:
	
	virtual std::queue<NetworkMessage> process(const NetworkMessage &) = 0;
	virtual std::queue<NetworkMessage> process(void) = 0;
	virtual bool isFlowOver(void) const noexcept = 0;
};