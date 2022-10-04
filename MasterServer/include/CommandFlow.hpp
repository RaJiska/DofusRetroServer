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
		ACCOUNT,
		END
	} FlowState;
	typedef std::unique_ptr<ICommand> CommandPtr;


	CommandFlow(FlowState flowState = FlowState::VERSION);
	virtual ~CommandFlow() = default;

	CommandPtr retrieveCommand();
	FlowState advanceFlow(ICommand::ExitStatus lastCommandStatus = ICommand::ExitStatus::OK);

	FlowState getFlowState() const noexcept;

	private:
	FlowState flowState;
	
	std::unordered_map<
		FlowState,
		std::function<CommandPtr(void)>
	> commandMap;

	void createClassMap(void);
	template<typename T>
	CommandPtr createCommand(void);
};