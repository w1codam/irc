#include "Command.hpp"

cPass::cPass(Server& server):
	Command(server, false)
{}

cPass::~cPass()
{}

void	cPass::Execute(Client* client, Arguments& arguments)
{
	std::string	pass(arguments.popArgument());

	if (client->Authenticated())
		return (void)client->queuePacket(ERR_ALREADYREGISTERED(client->getNickname()));

	client->setServerPassword(pass);
}
