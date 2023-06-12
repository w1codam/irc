#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>

#include "Server.hpp"
#include "Client.hpp"

class Server;

class Command
{
private:
	const bool			_authRequired;
protected:
	const Server&		_server;
public:
	explicit		Command(const Server& server, const bool authRequired = true);
	virtual			~Command();

	bool			authRequired();
	virtual void	Execute(Client* client, std::vector<std::string>& arguments) = 0;
};

#endif