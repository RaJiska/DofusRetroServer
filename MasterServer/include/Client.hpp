#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

#include "CommandFlow.hpp"
#include "Backend.hpp"

class Client
{
	public:
	Client(unsigned long long int id, boost::asio::io_service &ioService, Backend &backend);
	virtual ~Client() = default;

	virtual void start();
	virtual void end();

	virtual boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	void startRead();
	void handleRead(const boost::system::error_code &error, std::size_t len);
	void sendMessage(const std::string &message);
	void startWrite();
	void handleWrite(const boost::system::error_code &error, std::size_t len);
	bool processCommand();
	CommandFlow::FlowState updateCommandFlow(bool force = false);

	static const unsigned int BUFFER_SIZE = 256;

	unsigned long long int id;
	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::socket socket;
	Backend &backend;
	unsigned char buffer[Client::BUFFER_SIZE - 1];
	std::deque<std::string> messages;
	CommandFlow commandFlow;
	std::unique_ptr<ICommand> currentCommand = commandFlow.retrieveCommand();
};