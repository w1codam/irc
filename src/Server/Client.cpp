#include "Server.hpp"

Client*	Server::addClient(int fd)
{
	Client*	new_client;

	new_client = new Client;
	new_client->setSocket(fd);
	this->_clients[fd] = new_client;

	return new_client;
}

Client*	Server::getClient(int fd)
{
	return this->_clients.at(fd);
}

Client*	Server::getClient(std::string nickname)
{
	std::map<int, Client*>::iterator	it;

	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getNickname() == nickname)
			return it->second;
		++it;
	}
	throw std::runtime_error("could not find client");
}

void	Server::removeClient(int fd)
{
	std::map<int, Client*>::iterator	it;

	it = this->_clients.find(fd);

	if (it == this->_clients.end())	// should never happen
		throw std::runtime_error("removeClient() failure, client does not exist");

	delete it->second;
	this->_clients.erase(it);
}

