#include "Commands/Account.hpp"

#include "spdlog/spdlog.h"

Command::Account::Account(void) : ACommand()
{
	this->stepMap[Account::Step::VERSION] = std::bind(&Command::Account::handleVersion, this, std::placeholders::_1);
	this->stepMap[Account::Step::LOGIN] = std::bind(&Command::Account::handleLogin, this, std::placeholders::_1);
	this->stepMap[Account::Step::AF] = std::bind(&Command::Account::handleAf, this, std::placeholders::_1);
	// this->stepMap[Account::Step::END] = std::bind(&Command::Account::handleEnd, this, std::placeholders::_1);
}

void Command::Account::processMessage(const NetworkMessage &message)
{
	if (this->currentStep == Command::Account::Step::END)
		throw CommandException("Command is over and may not process messages anymore");
	this->stepMap[this->currentStep](message);
	this->currentStep = static_cast<Step>(static_cast<int>(this->currentStep) + 1);
}

void Command::Account::process(void)
{
	if (this->currentStep != Command::Account::Step::END)
		throw CommandException("Process may only be called once command is fully completed");
	if (this->exitStatus != OK) {
		if (this->dispatchList.empty()) {
			NetworkMessage err(NetworkMessage::Target::PEER, NetworkMessage::ERROR_UNFINISHED_CONNECTION);
			this->dispatchList.push(err);
		}
	}
	else {
		// Do Stuff
	}
}

bool Command::Account::isOver(void) const noexcept
{
	return this->currentStep == Command::Account::Step::END;
}

// ICommand::CommandState Command::Account::adjustStepAfterDispatch(void)
// {
// 	// Handle in case error message sent to dispatch
// 	if (this->dispatchFlag == DispatchFlag::FATAL) {
// 		this->exitStatus = ICommand::ExitStatus::FATAL;
// 		this->commandState = ICommand::CommandState::END;
// 	}
// 	else if (this->dispatchFlag == DispatchFlag::ERROR) {
// 		this->exitStatus = ICommand::ExitStatus::FATAL;
// 		this->commandState = ICommand::CommandState::END;
// 	}
// 	else {
// 		this->currentStep = static_cast<Command::Account::Step>(static_cast<int>(this->currentStep) + 1);
// 		this->commandState = this->stepMap[this->currentStep].first;
// 	}
// 	return this->commandState;
// }

void Command::Account::handleVersion(const NetworkMessage &msg)
{
	spdlog::debug("Command: Account: Received Version: {}", msg.getMessage());
	this->clientVersion = msg.getMessage();
}

void Command::Account::handleLogin(const NetworkMessage &msg)
{
	const std::string smsg = msg.getMessage();
	auto delim = smsg.find("\n#");

	spdlog::debug("Command: Account: Received Login: {}", smsg);
	if (delim > 0 && delim < smsg.size() - 2) {
		this->clientAccount = smsg.substr(0, delim - 1);
		this->clientPassword = smsg.substr(delim + 2);
	}
	else {
		NetworkMessage err(NetworkMessage::Target::PEER, NetworkMessage::ERROR_WRONG_PASS);
		this->dispatchList.push(err);
		this->exitStatus = ICommand::ExitStatus::ERROR;
	}
}

void Command::Account::handleAf(const NetworkMessage &msg)
{
	const std::string smsg = msg.getMessage();

	spdlog::debug("Command: Account: Received Af: {}", smsg);
	if (smsg != "Af\n")
		this->exitStatus = ICommand::ExitStatus::ERROR;
}
