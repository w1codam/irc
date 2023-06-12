#include "Command.hpp"

cUser::cUser(Server& server):
	Command(server, false)
{}

cUser::~cUser()
{}

void	cUser::Execute(Client* client, std::vector<std::string>& arguments)
{
	std::string		username	(Command::getArgument(arguments));
	std::string		mode    	(Command::getArgument(arguments));
	std::string		_			(Command::getArgument(arguments));
	std::string		realname	(Command::getArgument(arguments));

	if (client->getNickname().empty())
		return (void)client->queuePacket("NOIMPL: no nick set");

	client->setUsername(username);
	client->setRealname(realname);
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}
