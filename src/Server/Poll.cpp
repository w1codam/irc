#include "Server.hpp"

void	Server::addPoll(int fd, short events)
{
	pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;

	this->_pollfds.push_back(pfd);
}

void	Server::setPFlag(pollfd &pfd, short events)
{
	pfd.events |= events;
}

void	Server::removePFlag(pollfd &pfd, short events)
{
	pfd.events &= ~events;
}
