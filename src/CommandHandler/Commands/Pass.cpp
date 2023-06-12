#include "Command.hpp"

cPass::cPass(Server& server):
	Command(server, false)
{}

cPass::~cPass()
{}

void	cPass::Execute(Client* client, std::vector<std::string>& arguments)
{
	std::string	pass(Command::getArgument(arguments));
	(void)client;
}
