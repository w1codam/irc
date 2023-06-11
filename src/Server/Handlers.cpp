#include "Server.hpp"

void	Server::acceptClient()
{
	Client*	client;

	client = new Client;
	try
	{
		client->setSocket(
			Networking::Accept(this->_socket, &client->getAddr()));
		Networking::Setnonblocking(client->getSocket());
	}
	catch(const std::exception& e)
	{
		delete client;
		return;
	}
	this->_clients[client->getSocket()] = client;
	this->addPoll(client->getSocket(), POLLIN | POLLHUP);
	DEBUG(std::cout << "client connected (fd " << client->getSocket() << ")" << std::endl;)
}

bool	Server::handleData(Client* client)
{
	try
	{
		if (!client->receivePacket())
			return true;
		processPackets(client);
	}
	catch(const std::exception& e)
	{
		DEBUG(std::cerr << "error: " << e.what() << std::endl;)
		this->handleDisconnect(client);
		return false;
	}
	return true;
}

void	Server::processPackets(Client* client)
{
	std::string	packet;

	try
	{
		while (true) this->_commandHandler->Invoke(client, client->getPacket());	// process all packets
	}
	catch(const std::exception& e) {}
}

void	Server::handleDisconnect(Client* client)
{
	DEBUG(std::cout << "client disconnected (fd " << client->getSocket() << ")" << std::endl;)
	// remove client from all channels

	delete client;
}

