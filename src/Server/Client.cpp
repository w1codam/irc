#include "Server.hpp"

Client*	Server::addClient(int fd)
{
	Client*	new_client;

	new_client = new Client;
	new_client->setSocket(fd);

	return new_client;
}

Client*	Server::getClient(int fd)
{
	return this->_clients.at(fd);
}

void	Server::removeClient(int fd)
{
	std::map<int, Client*>::iterator	it;

	it = this->_clients.find(fd);
	delete it->second;

	this->_clients.erase(it);
}

