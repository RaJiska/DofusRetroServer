#pragma once

#include "ACommand.hpp"

namespace Command {
	class Version final : public ACommand
	{
		public:
		Version(void);
		~Version() = default;

		void processMessage(const NetworkMessage &message);

		protected:
		ICommand::CommandState adjustStepAfterDispatch(void);
	};
}