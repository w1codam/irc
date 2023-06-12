#include "Command.hpp"

cNick::cNick(Server& server):
	Command(server, false)
{}

cNick::~cNick()
{}

void	cNick::Execute(Client* client, std::vector<std::string>& arguments)
{
	std::string	nick(Command::getArgument(arguments));

	try
	{
		this->_server.getClient(nick);
		client->queuePacket("NOIMPL: nick in use");
	}
	catch (const std::exception& e)
	{
		client->setNickname(nick);
		client->queuePacket("NOIMPL: lmao nice bro!");
	}
}
