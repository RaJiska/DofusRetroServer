#include "CommandFlowLogin.hpp"

#include "Commands/Version.hpp"
#include "Commands/Account.hpp"

CommandFlowLogin::CommandFlowLogin() : ACommandFlow()
{
	this->commandMap[static_cast<int>(State::VERSION)] = std::bind(&CommandFlowLogin::createCommand<Command::Version>, this);
	this->commandMap[static_cast<int>(State::ACCOUNT)] = std::bind(&CommandFlowLogin::createCommand<Command::Account>, this);
	this->currentCommand = std::move(this->commandMap[this->state]());
}

void CommandFlowLogin::processMessage(const NetworkMessage &message)
{

}

std::queue<NetworkMessage> CommandFlowLogin::process(const NetworkMessage &message)
{
	std::queue<NetworkMessage> ret;

	this->currentCommand->processMessage(message);
	while (this->currentCommand->isOver()) {
		this->currentCommand->process();
		std::queue<NetworkMessage> tmp = this->currentCommand->consumeDispatchList();
		while (!tmp.empty()) {
			ret.push(tmp.front());
			tmp.pop();
		}
		this->state = this->state + 1;
		if (this->isFlowOver())
			break;
		else
			this->currentCommand = std::move(this->commandMap[this->state]());
	}
	return ret;
}

bool CommandFlowLogin::isFlowOver(void) const noexcept
{
	return static_cast<CommandFlowLogin::State>(this->state) == CommandFlowLogin::State::END;
}

template<typename T>
std::unique_ptr<ICommand> CommandFlowLogin::createCommand(void)
{
	return std::make_unique<T>();
}

// ProcessCommand() appeller une fois au debut
// ProcessCOmmand(Msg) a chaque read:
// 	1. Balance le msg
// 	2. while flow not end and command end:
// 		1. Process msg
// 		2. Save resp
// 		3. Update states/Command