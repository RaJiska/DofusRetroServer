#pragma once

#include <boost/asio.hpp>

#include "Client.hpp"

class MasterServer
{
	public:
	MasterServer() = default;
	MasterServer(boost::asio::io_service &ioService, std::uint16_t port);

	private:
	void startAccept();
	void handleAccept(Client *client, const boost::system::error_code &error);

	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;
};