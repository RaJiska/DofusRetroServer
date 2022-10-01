#include <iostream>
#include <list>
#include <boost/asio.hpp>

#include "MasterServer.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char * const *argv)
{
	return 0;
	try {
		boost::asio::io_service ioService;
		std::list<boost::shared_ptr<MasterServer>> msList;

		boost::shared_ptr<MasterServer> ms(new MasterServer(ioService, 1111));
		msList.push_back(ms);

		ioService.run();
	}
	catch (std::exception &e) {
		spdlog::error("Exception Occured: " + std::string(e.what()));
	}
	return 0;
}