#include "../../include/Networking.hpp"

ssize_t	Networking::Recv(int socket, void *buffer, size_t length)
{
	return ::recv(socket, buffer, length, 0);
}

ssize_t	Networking::Send(int socket, const void *buffer, size_t length)
{
	return ::send(socket, buffer, length, 0);
}
