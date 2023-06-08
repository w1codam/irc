#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "Networking.hpp"

class Client
{
private:
	int		_socket;
public:
	Client();
	~Client();

	void	setSocket(int fd);
	int		getSocket();
};

#endif