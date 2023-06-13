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

	// if (client->getNickname().empty())	// there is no error for when no nickname is set yet...?
	// 	return (void)client->queuePacket(ERR_NOTREGISTERED(client->getNickname()));

	if (client->Authenticated())
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));

	if (!this->_server.checkPassword(client->getServerPassword()))
		return (void)client->queuePacket(ERR_PASSWDMISMATCH(client->getNickname()));

	client->setUsername(username);
	client->setRealname(realname);

	if (client->getNickname().empty())
		return;

	client->setAuthenticated();
	client->queuePacket(RPL_WELCOME(client->getNickname()));
}
