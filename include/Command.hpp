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
	const bool		_authRequired;
	Server&			_server;
public:
	explicit		Command(Server& server, const bool authRequired);
	virtual			~Command();

	static std::string	getArgument(std::vector<std::string>& arguments);
	static std::string	joinArguments(std::vector<std::string>& arguments);

	bool				authRequired();
	virtual void		Execute(Client* client, std::vector<std::string>& arguments) = 0;
};

class cNick: public Command
{
public:
	cNick(Server& server);
	~cNick();
	void	Execute(Client* client, std::vector<std::string>& arguments);
};


class cPass: public Command
{
public:
	cPass(Server& server);
	~cPass();
	void	Execute(Client* client, std::vector<std::string>& arguments);
};


class cUser: public Command
{
public:
	cUser(Server& server);
	~cUser();
	void	Execute(Client* client, std::vector<std::string>& arguments);
};

#endif