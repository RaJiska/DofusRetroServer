#pragma once

#include "ACommand.hpp"

namespace Command {
	class Version final : public ACommand
	{
		public:
		Version(void);
		~Version() = default;

		bool isOver() const noexcept;
	};
}