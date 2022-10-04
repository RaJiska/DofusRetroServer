#pragma once

#include "ICommand.hpp"

#include <unordered_map>
#include <functional>

class ACommand : public ICommand
{
	public:
	ACommand(void);
	virtual ~ACommand() = default;

	std::queue<NetworkMessage> consumeDispatchList(void);

	ICommand::CommandState getCommandState(void) const noexcept;
	ICommand::ExitStatus getExitStatus(void) const noexcept;

	protected:
	typedef enum DispatchFlag {
		MSG,
		ERROR,
		FATAL
	} DispatchFlag;

	void pushMessagetoDispatchList(const NetworkMessage &message, DispatchFlag flag = DispatchFlag::MSG);
	virtual ICommand::CommandState adjustStepAfterDispatch() = 0;
	ICommand::CommandState handleEnd(const NetworkMessage &msg) const;

	ICommand::CommandState commandState = ICommand::CommandState::WAITING_FOR_INPUT;
	ICommand::ExitStatus exitStatus = ICommand::ExitStatus::OK;
	std::queue<NetworkMessage> dispatchList;
	DispatchFlag dispatchFlag = DispatchFlag::MSG;

};