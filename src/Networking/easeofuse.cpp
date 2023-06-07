#include "../../include/Networking.hpp"

void	Networking::Bind(int socket, short port)
{
	sockaddr_in	address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	Networking::Bind(socket, (sockaddr *)&address);
}

void	Networking::Setnonblocking(int socket)
{
	if (::fcntl(socket, F_SETFL, O_NONBLOCK) == -1)
		throw Networking::NetworkingException("fcntl() failure");
}
