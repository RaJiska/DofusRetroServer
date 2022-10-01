#pragma once

#include "ACommand.hpp"

namespace Command {
	class Version final : public ACommand
	{
		public:
		Version(void);
		~Version() = default;

		void processMessage(const NetworkMessage &message);
		void processCommand(void) noexcept;
		bool commandComplete(void) const noexcept;

		private:
		ICommand::CommandState handleSendHc();

		virtual void setNextStep(void) noexcept;
	};
}