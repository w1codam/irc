#include "Command.hpp"

cNick::cNick(Server& server):
	Command(server, false)
{

}

cNick::~cNick()
{}

void	cNick::Execute(Client* client, std::vector<std::string>& arguments)
{
	// validate nick here

	try
	{
		this->_server.getClient(arguments[0]);
		client->queuePacket("nick in use");
	}
	catch (const std::exception& e)
	{
		client->setNickname(arguments[0]);
		client->queuePacket("lmao nice bro!");
	}
}
