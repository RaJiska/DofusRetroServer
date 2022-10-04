#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>

#include "CommandFlow.hpp"
#include "Backend.hpp"
#include "MasterServer.hpp"

class MasterServer;

class Client
{
	public:
	Client(unsigned long long int id, boost::asio::io_service &ioService, Backend &backend, MasterServer &server);
	virtual ~Client() = default;

	virtual void start();
	virtual void end();

	virtual boost::asio::ip::tcp::socket &getSocket() noexcept;
	unsigned long long int getId() noexcept;
	void startRead();
	ICommand &getCurrentCommand() noexcept;
	void setCurrentCommand(CommandFlow::CommandPtr command) noexcept;
	void sendMessage(const NetworkMessage &message);
	CommandFlow &getCommandFlow() noexcept;

	private:
	void startWrite();
	void handleWrite(const boost::system::error_code &error, std::size_t len);

	static const unsigned int BUFFER_SIZE = 256;

	unsigned long long int id;
	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::socket socket;
	Backend &backend;
	std::queue<NetworkMessage> messages;
	CommandFlow commandFlow;
	std::unique_ptr<ICommand> currentCommand = commandFlow.retrieveCommand();
	MasterServer &masterServer;
};