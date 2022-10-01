#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

class Client
{
	public:
	Client(unsigned long long int id, boost::asio::io_service &ioService);
	virtual ~Client() = default;

	virtual void start();
	virtual void end();

	virtual boost::asio::ip::tcp::socket &getSocket() noexcept;

	private:
	void startRead();
	void handleRead(const boost::system::error_code &error, std::size_t len);
	void sendMessage(std::string const& message);
	void handleWrite(const boost::system::error_code &error, std::size_t len);

	static const unsigned int BUFFER_SIZE = 256;

	unsigned long long int id;
	boost::asio::io_service &ioService;
	boost::asio::ip::tcp::socket socket;
	unsigned char buffer[Client::BUFFER_SIZE - 1];
};