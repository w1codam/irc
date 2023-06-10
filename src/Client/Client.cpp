#include "Client.hpp"

Client::Client():
	_socket(-1)
{
}

Client::~Client()
{
	Networking::Close(this->_socket);
}

void Client::setSocket(int fd)
{
	this->_socket = fd;
}

int	 Client::getSocket()
{
	return this->_socket;
}

sockaddr_in&	Client::getAddr()
{
	return this->_addr;
}
