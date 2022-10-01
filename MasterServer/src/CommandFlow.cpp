#include "CommandFlow.hpp"

#include "Commands/Version.hpp"

CommandFlow::CommandFlow(CommandFlow::FlowState flowState) : flowState(flowState)
{
	this->createClassMap();
}

CommandFlow::CommandPtr CommandFlow::retrieveCommand()
{
	return std::move(this->commandMap[this->flowState]());
}

CommandFlow::FlowState CommandFlow::advanceFlow()
{
	if (this->flowState == CommandFlow::FlowState::END)
		throw std::out_of_range("FlowState has already reached its end");
	this->flowState = static_cast<CommandFlow::FlowState>(static_cast<int>(this->flowState) + 1);
	return this->flowState;
}

CommandFlow::FlowState CommandFlow::getFlowState() const noexcept
{
	return this->flowState;
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

