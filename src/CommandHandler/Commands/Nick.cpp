#include "Command.hpp"

cNick::cNick(Server& server):
	Command(server, false)
{}

cNick::~cNick()
{}

void	cNick::Execute(Client* client, Arguments& arguments)
{
	std::string	nick(arguments.popArgument());

	if (this->_server.getClient(nick))
		return (void)client->queuePacket(ERR_NICKNAMEINUSE(client->getNickname()));

	client->setNickname(nick);
}
