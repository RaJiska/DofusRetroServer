#include "Client.hpp"

#include <iostream>
#include <boost/bind.hpp>

#include "spdlog/spdlog.h"

Client::Client(unsigned long long int id, boost::asio::io_service &ioService, Backend &backend, MasterServer &server) :
	id(id), ioService(ioService), socket(ioService), backend(backend), masterServer(server)
{

}

void Client::start()
{
	spdlog::info("New client with ID " + std::to_string(this->id) + " (" +
		this->socket.remote_endpoint().address().to_string() + ":" +
		std::to_string(this->socket.remote_endpoint().port()) + ")"
	);
	auto msgs = this->commandFlow->process();
	this->consumeMessages(msgs);
	this->startRead();
}

void Client::startRead()
{
	static unsigned char buffer[Client::BUFFER_SIZE - 1];

	boost::asio::post(this->ioService, [this]() {
		boost::asio::async_read(this->socket,
			boost::asio::buffer(&buffer[0], Client::BUFFER_SIZE - 1),
			boost::asio::transfer_at_least(1),
			boost::bind(
				&MasterServer::handleRead,
				&this->masterServer,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred,
				this,
				&buffer[0]
			)
		);
	});
}

void Client::end()
{
	boost::asio::post(this->ioService, [this]() {
		spdlog::info("Client disconnected with ID " + std::to_string(this->id) + " (" +
			this->socket.remote_endpoint().address().to_string() + ":" +
			std::to_string(this->socket.remote_endpoint().port()) + ")"
		);
		this->socket.close();
	});
}

void Client::sendMessage(const NetworkMessage &message)
{
	bool isWriteInProgress = !this->messages.empty();
	this->messages.push(message);
	if (!isWriteInProgress) {
		this->startWrite();
	}
}

void Client::consumeMessages(std::queue<NetworkMessage> &messages)
{
	while (!messages.empty()) {
		this->sendMessage(messages.front());
		messages.pop();
	}
}

void Client::startWrite()
{
	boost::asio::async_write(this->socket,
		boost::asio::buffer(
			this->messages.front().getMessage() + '\0', 
			this->messages.front().getMessage().size() + 1
		),
		boost::bind(
			&Client::handleWrite,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void Client::handleWrite(const boost::system::error_code &error, std::size_t len)
{
	if (!error && len > 0) {
		spdlog::info("Sent Msg to ID {0}: {1} bytes", this->id, len);
		this->messages.pop();
		if (!this->messages.empty()) {
			startWrite();
		}
	} else {
		spdlog::error("Error sending message to {0}: {1}", this->id, error.message());
		this->end();
	}
}

boost::asio::ip::tcp::socket &Client::getSocket() noexcept
{
	return this->socket;
}

unsigned long long int Client::getId() const noexcept
{
	return this->id;
}

std::shared_ptr<ICommandFlow> Client::getCommandFlow()
{
	return this->commandFlow;
}