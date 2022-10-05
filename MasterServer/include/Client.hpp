#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>

#include "Backend.hpp"
#include "MasterServer.hpp"
#include "NetworkMessage.hpp"
#include "CommandFlowLogin.hpp"

class MasterServer;

class Client
{
	public:
	Client(unsigned long long int id, boost::asio::io_service &ioService, Backend &backend, MasterServer &server);
	virtual ~Client() = default;

	virtual void start();
	virtual void end();

	void startRead();
	void sendMessage(const NetworkMessage &message);
	void consumeMessages(std::queue<NetworkMessage> &messages);

	boost::asio::ip::tcp::socket &getSocket() noexcept;
	unsigned long long int getId() const noexcept;
	std::shared_ptr<ICommandFlow> getCommandFlow();

	private:
	void startWrite();
	void handleWrite(const boost::system::error_code &error, std::size_t len);

	static const unsigned int BUFFER_SIZE = 256;

	unsigned long long int id;
	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::socket socket;
	Backend &backend;
	MasterServer &masterServer;

	std::queue<NetworkMessage> messages;
	std::shared_ptr<ICommandFlow> commandFlow = std::make_unique<CommandFlowLogin>();
};