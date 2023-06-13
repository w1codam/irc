#include "Command.hpp"

cUser::cUser(Server& server):
	Command(server, false)
{}

cUser::~cUser()
{}

void	cUser::Execute(Client* client, Arguments& arguments)
{
	std::string	username	(arguments.popArgument());
	std::string	mode    	(arguments.popArgument());
	std::string	_			(arguments.popArgument());
	std::string	realname	(arguments.popArgument());

	if (client->getNickname().empty())
		return (void)client->queuePacket("NOIMPL: no nick set");

	client->setUsername(username);
	client->setRealname(realname);
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}
