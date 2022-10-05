#include "MasterServer.hpp"

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
	static unsigned long long int id = -1;
	std::unique_ptr<Client> client(new Client(++id, this->ioService, this->backend, *this));
	this->clients.push_back(std::move(client));
	unsigned long long int clientIndex = getClientById(id);
	this->acceptor.async_accept(this->clients[clientIndex]->getSocket(), boost::bind(
		&MasterServer::handleAccept,
		this,
		boost::asio::placeholders::error,
		clientIndex
	));
}

void MasterServer::handleAccept(const boost::system::error_code &error, unsigned long long int clientIndex)
{	
	if (!error) {
		this->clients[clientIndex]->start();
	} else {
		spdlog::error("Could not accept new client: {0}", error.message());
		this->clients.erase(this->clients.begin() + clientIndex);
	}
	this->startAccept();
}

void MasterServer::handleRead(const boost::system::error_code &error, std::size_t len, Client *client, unsigned char *buffer)
{
	if (!error && len > 0) {
		NetworkMessage msg(NetworkMessage::Target::PEER, reinterpret_cast<const char *>(buffer), len, true);
		auto commandFlow = client->getCommandFlow();

		spdlog::debug("Received Msg from ID {0}: '{1}' ({2} bytes)", client->getId(), msg.getMessage(), len);
		auto msgs = commandFlow->process(msg);
		client->consumeMessages(msgs);
		if (!commandFlow->isFlowOver())
			client->startRead();
		else
			client->end();
	}
	else {
		client->end();
	}
}

unsigned long long int MasterServer::getClientById(unsigned long long int id)
{
    for (int i = 0; i < this->clients.size(); i++) {
		if (this->clients[i]->getId() == id) {
			return i;
		}
    }
}