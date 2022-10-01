#include "Client.hpp"

#include <iostream>
#include <boost/bind.hpp>

#include "spdlog/spdlog.h"

Client::Client(unsigned long long int id, boost::asio::io_service &ioService) :
	id(id), ioService(ioService), socket(ioService)
{

}

void Client::start()
{
	spdlog::info("New client with ID " + std::to_string(this->id) + " (" +
		this->socket.remote_endpoint().address().to_string() + ":" +
		std::to_string(this->socket.remote_endpoint().port()) + ")"
	);
	this->startRead();
}

void Client::startRead()
{
	boost::asio::post([this]() {
		boost::asio::async_read(this->socket,
			boost::asio::buffer(&this->buffer[0], Client::BUFFER_SIZE),
			boost::asio::transfer_at_least(1),
			boost::bind(
				&Client::handleRead,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	});
}

void Client::end()
{
	boost::asio::post([this]() {
		spdlog::info("Client disconnected with ID " + std::to_string(this->id) + " (" +
			this->socket.remote_endpoint().address().to_string() + ":" +
			std::to_string(this->socket.remote_endpoint().port()) + ")"
		);
		this->socket.close();
	});
}

boost::asio::ip::tcp::socket &Client::getSocket() noexcept
{
	return this->socket;
}

void Client::handleRead(const boost::system::error_code &error, std::size_t len)
{
	if (!error && len > 0) {
		spdlog::info("Received Msg from ID {0}: {1} bytes", this->id, len);
		// Do Something
		this->startRead();
	}
	else
		this->end();
}

void Client::sendMessage(std::string const &message)
{
	boost::asio::post([this, message]() {
		boost::asio::async_write(this->socket,
			boost::asio::buffer(message, message.size()),
			boost::asio::transfer_at_least(1),
			boost::bind(
				&Client::handleWrite,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	});
}

void Client::handleWrite(const boost::system::error_code &error, std::size_t len)
{
	if (!error && len > 0) {
		spdlog::info("Sent Msg to ID {0}: {1} bytes", this->id, len);
	} else {
		spdlog::error("Error sending message to {0}", this->id);
		this->end();
	}
}