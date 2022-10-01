#include "CommandFlow.hpp"

#include "Commands/Version.hpp"

CommandFlow::CommandFlow()
{
	this->createClassMap();
	this->command = this->commandMap[this->flowState]();
}

void CommandFlow::createClassMap(void)
{
	this->commandMap[CommandFlow::VERSION] = std::bind(&CommandFlow::createCommand<Command::Version>, this);
}

template <typename T>
CommandFlow::CommandPtr CommandFlow::createCommand(void)
{
	return std::make_unique<T>();
}

