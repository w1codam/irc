#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>

#include "Server.hpp"
#include "Client.hpp"

class Server;

class Command
{
protected:
	const Server&		_server;
	const bool			_authRequired;
public:
	explicit		Command(const Server& server, const bool authRequired);
	virtual			~Command();

	virtual void	Execute(Client* client, std::vector<std::string>& arguments) = 0;
};

#endif