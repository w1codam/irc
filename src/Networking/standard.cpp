#include "../../include/Networking.hpp"

int	Networking::Socket()
{
	int	fd;

	fd = ::socket(PF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw Networking::NetworkingException("socket() failure");
	return (fd);
}

int	Networking::Accept(int socket, sockaddr_in *address)
{
	int			fd;
	socklen_t	len;

	len = sizeof(sockaddr_in);
	fd = ::accept(socket, (sockaddr*)address, &len);
	if (fd == -1)
		throw Networking::NetworkingException("accept() failure");
	return (fd);
}

void	Networking::Bind(int socket, const sockaddr *address)
{
	if (::bind(socket, address, sizeof(sockaddr)))
		throw Networking::NetworkingException("bind() failure");
}

void	Networking::Setsockopt(int socket, int option_name, int option_value)
{
	if (::setsockopt(socket, SOL_SOCKET, option_name, &option_value, sizeof(option_value)))
		throw Networking::NetworkingException("setsockopt() failure");
}

void	Networking::Listen(int socket, int backlog)
{
	if (::listen(socket, backlog))
		throw Networking::NetworkingException("listen() failure");
}

int		Networking::Poll(pollfd fds[], nfds_t nfds, int timeout)
{
	if (::poll(fds, nfds, timeout) == -1)
		throw Networking::NetworkingException("poll() failure");
}
