#pragma once

#include "ACommand.hpp"

namespace Command {
	class Account final : public ACommand
	{
		public:
		Account(void);
		~Account() = default;

		void processMessage(const NetworkMessage &message);

		protected:
		ICommand::CommandState adjustStepAfterDispatch(void);

		private:
		typedef enum Step {
			VERSION,
			LOGIN,
			END
		} Step;

		ICommand::CommandState handleVersion(const NetworkMessage &msg);
		ICommand::CommandState handleLogin(const NetworkMessage &msg);

		Step currentStep = static_cast<Step>(0);
		std::unordered_map<Step, std::pair<
				ICommand::CommandState,
				std::function<ICommand::CommandState(const NetworkMessage &)>
			>
		> stepMap;
	};
}