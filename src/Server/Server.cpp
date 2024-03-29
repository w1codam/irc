#include "Server.hpp"

Server::Server(std::string port, std::string password):
	_socket(-1),
	_port(atoi(port.c_str())),
	_password(password),
	_commandHandler(new CommandHandler(*this))
{
	// socket server setup
	this->_socket = Networking::Socket();
	Networking::Setnonblocking(this->_socket);
	Networking::Setsockopt(this->_socket, SO_REUSEPORT, 1);
	Networking::Bind(this->_socket, INADDR_ANY, this->_port);
	Networking::Listen(this->_socket, 1);

	this->addPoll(this->_socket, POLLIN);
}

Server::~Server()
{
	std::map<std::string, Channel*>::iterator	channel_it;
	std::map<int, Client*>::iterator			client_it;

	delete _commandHandler;
	Networking::Close(this->_socket);

	// delete all channels
	channel_it = this->_channels.begin();
	while (channel_it != this->_channels.end())
	{
		delete channel_it->second;
		++channel_it;
	}

	// delete all users
	client_it = this->_clients.begin();
	while (client_it != this->_clients.end())
	{
		delete client_it->second;
		++client_it;
	}
}

bool	Server::checkPassword(std::string password)
{
	return this->_password == password;
}

void	Server::Serve()
{
	size_t							nfds;
	Client*							client;
	std::vector<pollfd>::iterator	it;

	nfds = this->_pollfds.size();
	Networking::Poll(this->_pollfds.data(), nfds, -1);
	
	// check server fd aside from clients
	if (this->_pollfds[0].revents & POLLIN)
	{
		this->_pollfds[0].revents = 0;
		this->acceptClient();
	}

	// loop over all clients
	for (size_t index = 1; index < nfds; index++)
	{
		pollfd&	pfd = this->_pollfds[index];	// prefer a reference for this
		client = this->getClient(pfd.fd);

		if (pfd.revents & POLLHUP)
		{
			this->handleDisconnect(client);
			this->removePFlag(pfd, 0xFFFF);			// zero out events so we know this client needs to be removed
			continue;
		}

		if (pfd.revents & POLLIN)					// ready for incoming data
			if (!this->handleData(client))			// if it fails, mark pfd for deletion
				this->removePFlag(pfd, 0xFFFF);
		
		if (pfd.revents & POLLOUT)					// ready for outgoing data
			if (client->processQueue())				// if queue gets processed, remove POLLOUT
				this->removePFlag(pfd, POLLOUT);

		pfd.revents = 0;
	}

	// remove all pfds with events zeroed out
	it = ++this->_pollfds.begin();	// ++ because first fd is server
	while (it != this->_pollfds.end())
	{
		if (!it->events)	it = this->_pollfds.erase(it);
		else				++it;
	}

	// set POLLOUT if queue not empty
	it = ++this->_pollfds.begin();	// ++ because first fd is server
	while (it != this->_pollfds.end())
	{
		client = this->getClient(it->fd);
		if (client->getQueueSize())
			this->setPFlag(*it, POLLOUT);
		++it;
	}
}

in_port_t	Server::getPort()
{
	return this->_port;
}
