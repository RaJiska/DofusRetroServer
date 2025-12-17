#include <iostream>
#include <list>
#include <boost/asio.hpp>

#include "MasterServer.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char * const *argv)
{
#ifdef DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif
	std::list<boost::shared_ptr<MasterServer>> msList;

	try {
		boost::asio::io_context ioContext;

		boost::shared_ptr<MasterServer> ms(new MasterServer(ioContext, 1111));
		msList.push_back(ms);

		ioContext.run();
	}
	catch (std::exception &e) {
		spdlog::error("Exception Occured: " + std::string(e.what()));
	}
	return 0;
}