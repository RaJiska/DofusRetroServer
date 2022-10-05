#pragma once

#include "ACommandFlow.hpp"
#include "Exceptions/CommandFlowException.hpp"

class CommandFlowLogin : public ACommandFlow
{
	public:
	CommandFlowLogin();
	virtual ~CommandFlowLogin() = default;

	void processMessage(const NetworkMessage &message);
	std::queue<NetworkMessage> process(const NetworkMessage &message);
	bool isFlowOver(void) const noexcept;

	private:
	typedef enum State {
		VERSION,
		ACCOUNT,
		END
	} State;

	template<typename T> std::unique_ptr<ICommand> createCommand(void);
	std::queue<NetworkMessage> processCommand(const NetworkMessage &msg);
};
