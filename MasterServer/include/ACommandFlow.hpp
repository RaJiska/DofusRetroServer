#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "ICommandFlow.hpp"
#include "ICommand.hpp"

class ACommandFlow : public ICommandFlow
{
	public:
	ACommandFlow();
	virtual ~ACommandFlow() = default;

	std::queue<NetworkMessage> process(void);
	
	protected:
	std::unordered_map<unsigned, std::function<std::unique_ptr<ICommand>(void)>> commandMap;
	std::unique_ptr<ICommand> currentCommand;
	unsigned state = 0;
};