#include "Command.hpp"

cPass::cPass(Server& server):
	Command(server, false)
{}

cPass::~cPass()
{}

void	cPass::Execute(Client* client, Arguments& arguments)
{
	std::string	pass(arguments.popArgument());
	(void)client;
}
