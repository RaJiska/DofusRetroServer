#pragma once

#include "ACommand.hpp"

namespace Command {
	class Account final : public ACommand
	{
		public:
		Account(void);
		~Account() = default;

		virtual void processMessage(const NetworkMessage &message) override;
		void process(void) override;
		bool isOver(void) const noexcept override;

		protected:

		private:
		typedef enum Step {
			VERSION,
			LOGIN,
			AF,
			END
		} Step;

		void handleVersion(const NetworkMessage &msg);
		void handleLogin(const NetworkMessage &msg);
		void handleAf(const NetworkMessage &msg);

		Step currentStep = static_cast<Step>(0);
		std::unordered_map<Step, std::function<void(const NetworkMessage &)>> stepMap;

		std::string clientVersion = "";
		std::string clientAccount = "";
		std::string clientPassword = "";
	};
}