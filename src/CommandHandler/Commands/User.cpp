#include "Command.hpp"

cUser::cUser(Server& server):
	Command(server, false)
{}

cUser::~cUser()
{}

void	cUser::Execute(Client* client, std::vector<std::string>& arguments)
{
	std::string		username(arguments.at(0));
	std::string		mode    (arguments.at(1));
	std::string		realname(arguments.at(3));

	if (client->getNickname().empty())
		return (void)client->queuePacket(ERR_UNKNOWNERROR("USER"));

	client->setUsername(username);
	client->setRealname(realname);
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}
