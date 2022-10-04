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

void MasterServer::handleRead(const boost::system::error_code &error, std::size_t len, Client *client, unsigned char buffer[])
{
	if (!error && len > 0) {
		NetworkMessage msg(NetworkMessage::Target::PEER, reinterpret_cast<const char *>(buffer), len);

		spdlog::debug("Received Msg from ID {0}: '{1}' ({2} bytes)", client->getId(), msg.getMessage(), len);

		client->getCurrentCommand().processMessage(msg);
		while (this->processCommand(*client)) {
			if (this->updateCommandFlow(*client) == CommandFlow::FlowState::END) {
				return;
			}
		}
		client->startRead();
	}
}

bool MasterServer::processCommand(Client &client)
{
	bool actionPerformed = false;
	auto commandState = client.getCurrentCommand().getCommandState();

	while (commandState == ICommand::CommandState::MESSAGES_TO_DISPATCH) {
		std::queue<NetworkMessage> msgs = client.getCurrentCommand().consumeDispatchList();
		while (!msgs.empty()) {
			client.sendMessage(msgs.front());
			msgs.pop();
		}
		commandState = client.getCurrentCommand().getCommandState();
		actionPerformed = true;
	}
	if (commandState == ICommand::CommandState::END) {
		actionPerformed = true;
	}
	return actionPerformed;
}

CommandFlow::FlowState MasterServer::updateCommandFlow(Client &client, bool force)
{
	CommandFlow::FlowState flowState = client.getCommandFlow().getFlowState();

	if (force || client.getCurrentCommand().getCommandState() == ICommand::CommandState::END) {
		auto previousFlowState = flowState;
		auto exitStatus = client.getCurrentCommand().getExitStatus();
		if (exitStatus == ICommand::ExitStatus::ERROR || exitStatus == ICommand::ExitStatus::FATAL)
			spdlog::debug("Client {0} had their command {1} exited in error with {2}", client.getId(), flowState, exitStatus);
		flowState = client.getCommandFlow().advanceFlow(exitStatus);
		spdlog::debug("Client {0} advanced command flow from {1} to {2}", client.getId(), previousFlowState, client.getCommandFlow().getFlowState());
		if (flowState != CommandFlow::FlowState::END) {
			client.setCurrentCommand(client.getCommandFlow().retrieveCommand());
		}
		else {
			spdlog::debug("Client {} reached the end of their command flow", client.getId());
			client.end();
		}
	}
	return flowState;
}

unsigned long long int MasterServer::getClientById(unsigned long long int id)
{
    for (int i = 0; i < this->clients.size(); i++) {
		if (this->clients[i]->getId() == id) {
			return i;
		}
    }
}