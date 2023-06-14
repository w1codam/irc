#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Arguments.hpp"

class Channel;
class Server;

class Command
{
protected:
	const bool		_authRequired;
	Server&			_server;
public:
	explicit		Command(Server& server, const bool authRequired);
	virtual			~Command();

	bool				authRequired();
	virtual void		Execute(Client* client, Arguments& arguments) = 0;
};

class cNick: public Command
{
public:
	cNick(Server& server);
	~cNick();
	void	Execute(Client* client, Arguments& arguments);
};


class cPass: public Command
{
public:
	cPass(Server& server);
	~cPass();
	void	Execute(Client* client, Arguments& arguments);
};


class cUser: public Command
{
public:
	cUser(Server& server);
	~cUser();
	void	Execute(Client* client, Arguments& arguments);
};


class cJoin: public Command
{
public:
	cJoin(Server& server);
	~cJoin();
	void	Execute(Client* client, Arguments& arguments);
};

class cPrivMsg: public Command
{
public:
	cPrivMsg(Server& server);
	~cPrivMsg();
	void	toChannel(Client* client, std::string& target, Arguments& arguments);
	void	toClient(Client* client, std::string& target, Arguments& arguments);
	void	Execute(Client* client, Arguments& arguments);
};

class cKick: public Command
{
public:
	cKick(Server& server);
	~cKick();
	void	Execute(Client* client, Arguments& arguments);
};

class cTopic: public Command
{
public:
	cTopic(Server& server);
	~cTopic();
	void	Execute(Client* client, Arguments& arguments);
};

class cInvite: public Command
{
public:
	cInvite(Server& server);
	~cInvite();
	void	Execute(Client* client, Arguments& arguments);
};


#endif