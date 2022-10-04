#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Client.hpp"
#include "Backend.hpp"

class Client;

class MasterServer
{
	public:
	MasterServer() = default;
	MasterServer(boost::asio::io_service &ioService, std::uint16_t port);
	void handleRead(const boost::system::error_code &error, std::size_t len, Client *client, unsigned char[]);

	private:
	void startAccept();
	void handleAccept(const boost::system::error_code &error, unsigned long long int id);
	bool processCommand(Client &client);
	CommandFlow::FlowState updateCommandFlow(Client &client, bool force = false);
	unsigned long long int getClientById(unsigned long long int id);

	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;
	Backend backend;
	std::deque<std::unique_ptr<Client>> clients;
};