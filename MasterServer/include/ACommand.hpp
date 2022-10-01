#pragma once

#include "ICommand.hpp"

#include <unordered_map>
#include <functional>
#include <queue>

class ACommand : public ICommand
{
	public:
	ACommand(void);
	virtual ~ACommand() = default;

	virtual ICommand::CommandState getCommandState(void) const noexcept;

	protected:
	ICommand::CommandState commandState = ICommand::CommandState::WAITING_FOR_INPUT;
	std::queue<NetworkMessage> dispatchList;

	private:
	virtual void setNextStep(void) noexcept = 0;
};