#include "MasterServer.hpp"

#include <boost/bind.hpp>

#include "spdlog/spdlog.h"

MasterServer::MasterServer(boost::asio::io_service &ioService, std::uint16_t port) :
	ioService(ioService),
	acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	socket(ioService)
{
	spdlog::info("Accepting connections on port " + std::to_string(port));
	this->startAccept();
}

void MasterServer::startAccept()
{
	static unsigned long long int id = 0;
	Client *client = new Client(id++, this->ioService);

	this->acceptor.async_accept(client->getSocket(), boost::bind(
		&MasterServer::handleAccept,
		this,
		client,
		boost::asio::placeholders::error
	));
}

void MasterServer::handleAccept(Client *client, const boost::system::error_code &error)
{
	if (!error)
		client->start();
	else {
		spdlog::error("Could not accept new client: %s", error.message());
		delete client;
	}
	this->startAccept();
}