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
	virtual void processMessage(const NetworkMessage &message);
	virtual void process(void);

	ICommand::ExitStatus getExitStatus(void) const noexcept;

	protected:
	std::queue<NetworkMessage> dispatchList;
	ICommand::ExitStatus exitStatus = ICommand::ExitStatus::OK;


	// typedef enum DispatchFlag {
	// 	MSG,
	// 	ERROR,
	// 	FATAL
	// } DispatchFlag;

	// void pushMessagetoDispatchList(const NetworkMessage &message, DispatchFlag flag = DispatchFlag::MSG);
	// virtual ICommand::CommandState adjustStepAfterDispatch() = 0;
	// ICommand::CommandState handleEnd(const NetworkMessage &msg) const;

	// ICommand::CommandState commandState = ICommand::CommandState::WAITING_FOR_INPUT;
	// ICommand::ExitStatus exitStatus = ICommand::ExitStatus::OK;
	// DispatchFlag dispatchFlag = DispatchFlag::MSG;

};