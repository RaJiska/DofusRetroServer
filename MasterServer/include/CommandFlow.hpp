#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "ICommand.hpp"

class CommandFlow
{
	public:
	typedef enum FlowState
	{
		VERSION,
		CREDENTIALS,
	} FlowState;
	typedef std::unique_ptr<ICommand> CommandPtr;


	CommandFlow();
	virtual ~CommandFlow() = default;

	std::unique_ptr<ICommand> command;

	private:
	FlowState flowState = FlowState::VERSION;
	std::unordered_map<
		FlowState,
		std::function<CommandPtr(void)>
	> commandMap;

	void createClassMap(void);
	template<typename T>
	CommandPtr createCommand(void);
};