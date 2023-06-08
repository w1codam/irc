#include "Server.hpp"

Server::Server(std::string port, std::string password):
	_port(std::stoi(port)),
	_password(password),
	_socket(-1)
{
	// socket server setup
	this->_socket = Networking::Socket();
	Networking::Setnonblocking(this->_socket);
	Networking::Setsockopt(this->_socket, SO_REUSEPORT, 1);
	Networking::Bind(this->_socket, INADDR_ANY, this->_port);
	Networking::Listen(this->_socket, 1);
}

Server::~Server()
{
	Networking::Close(this->_socket);

	// delete all channels
	// delete all users
}

