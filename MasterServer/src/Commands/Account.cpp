#include "Commands/Account.hpp"

#include "spdlog/spdlog.h"

Command::Account::Account(void) : ACommand()
{
	this->stepMap[Account::Step::VERSION] = std::make_pair(
		ICommand::CommandState::WAITING_FOR_INPUT,
		std::bind(&Command::Account::handleVersion, this, std::placeholders::_1)
	);
	this->stepMap[Account::Step::LOGIN] = std::make_pair(
		ICommand::CommandState::WAITING_FOR_INPUT,
		std::bind(&Command::Account::handleLogin, this, std::placeholders::_1)
	);
	this->stepMap[Account::Step::END] = std::make_pair(
		ICommand::CommandState::END,
		std::bind(&Command::Account::handleEnd, this, std::placeholders::_1)
	);
	this->commandState = this->stepMap[static_cast<Account::Step>(0)].first;
}

void Command::Account::processMessage(const NetworkMessage &message)
{
	if (this->commandState != ICommand::CommandState::WAITING_FOR_INPUT)
		throw CommandException("Command not expecting an input");
	this->stepMap[Account::Step::VERSION].second(message);
}

ICommand::CommandState Command::Account::adjustStepAfterDispatch(void)
{
	// Handle in case error message sent to dispatch
	if (this->dispatchFlag == DispatchFlag::FATAL) {
		this->exitStatus = ICommand::ExitStatus::FATAL;
		this->commandState = ICommand::CommandState::END;
	}
	else if (this->dispatchFlag == DispatchFlag::ERROR) {
		this->exitStatus = ICommand::ExitStatus::FATAL;
		this->commandState = ICommand::CommandState::END;
	}
	else {
		this->currentStep = static_cast<Command::Account::Step>(static_cast<int>(this->currentStep) + 1);
		this->commandState = this->stepMap[this->currentStep].first;
	}
	return this->commandState;
}

ICommand::CommandState Command::Account::handleVersion(const NetworkMessage &msg)
{
	spdlog::debug("Command: Account: Received version: {}", msg.getMessage());
	if (true) {
		// If all good
		this->currentStep = static_cast<Command::Account::Step>(static_cast<int>(this->currentStep) + 1);
		this->commandState = this->stepMap[this->currentStep].first;
	}
	else {
		NetworkMessage error(NetworkMessage::Target::PEER, "Alef");
		this->pushMessagetoDispatchList(error, DispatchFlag::FATAL);
		this->commandState = ICommand::CommandState::MESSAGES_TO_DISPATCH;
	}
	return this->commandState;
}

ICommand::CommandState Command::Account::handleLogin(const NetworkMessage &msg)
{
	spdlog::debug("Command: Account: Received Account: {}", msg.getMessage());
	if (true) {
		// If all good
		this->currentStep = static_cast<Command::Account::Step>(static_cast<int>(this->currentStep) + 1);
		this->commandState = this->stepMap[this->currentStep].first;
	}
	else {
		NetworkMessage error(NetworkMessage::Target::PEER, "Alef");
		this->pushMessagetoDispatchList(error, DispatchFlag::FATAL);
		this->commandState = ICommand::CommandState::MESSAGES_TO_DISPATCH;
	}
	return this->commandState;
}
