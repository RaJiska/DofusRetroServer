#include "Client.hpp"

#include <iostream>
#include <boost/bind.hpp>

#include "spdlog/spdlog.h"

Client::Client(unsigned long long int id, boost::asio::io_service &ioService, Backend &backend) :
	id(id), ioService(ioService), socket(ioService), backend(backend)
{

}

void Client::start()
{
	spdlog::info("New client with ID " + std::to_string(this->id) + " (" +
		this->socket.remote_endpoint().address().to_string() + ":" +
		std::to_string(this->socket.remote_endpoint().port()) + ")"
	);
	if (this->processCommand() && this->updateCommandFlow() != CommandFlow::FlowState::END) {
		this->startRead();
	}
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
		if (this->processCommand() && this->updateCommandFlow() != CommandFlow::FlowState::END) {
			this->startRead();
		}
	}
	else
		this->end();
}

void Client::sendMessage(const std::string &message)
{
    bool isWriteInProgress = !this->messages.empty();
    this->messages.push_back(message);
    if (!isWriteInProgress)
    {
      this->startWrite();
    }
}

void Client::startWrite()
{
	boost::asio::post([this]() {
		boost::asio::async_write(this->socket,
			boost::asio::buffer(this->messages.front(), this->messages.front().size()),
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
		this->messages.pop_front();
		if (!this->messages.empty()) {
			startWrite();
		}
	} else {
		spdlog::error("Error sending message to {0}", this->id);
		this->end();
	}
}

bool Client::processCommand()
{
	bool actionPerformed = false;
	auto commandState = this->currentCommand->getCommandState();

	while (commandState == ICommand::CommandState::MESSAGES_TO_DISPATCH) {
		// Process NetworkMessage
		commandState = this->currentCommand->advanceStep();
		actionPerformed = true;
	}
	if (commandState == ICommand::CommandState::END) {
		actionPerformed = true;
	}
	return actionPerformed;
}

CommandFlow::FlowState Client::updateCommandFlow(bool force)
{
	CommandFlow::FlowState flowState = this->commandFlow.getFlowState();

	if (force || this->currentCommand->getCommandState() == ICommand::CommandState::END) {
		flowState = this->commandFlow.advanceFlow();
		if (flowState != CommandFlow::FlowState::END) {
			this->currentCommand = this->commandFlow.retrieveCommand();
		}
		else {
			spdlog::debug("Client {} reached the end of their command flow", this->id);
			this->end();
		}
	}
	return flowState;
}