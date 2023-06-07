#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server
{
private:
	short			_port;
	std::string		_password;
public:
	Server(std::string port, std::string password);
};

#endif