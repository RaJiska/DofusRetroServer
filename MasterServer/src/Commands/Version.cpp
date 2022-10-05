#include "Commands/Version.hpp"

Command::Version::Version(void) : ACommand()
{
	NetworkMessage msg(NetworkMessage::Target::PEER, "HCaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	this->dispatchList.push(msg);
}

bool Command::Version::isOver() const noexcept
{
	return true;
}
