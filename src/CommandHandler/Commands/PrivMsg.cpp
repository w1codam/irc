#include "Command.hpp"

cPrivMsg::cPrivMsg(Server& server):
	Command(server, true)
{}

cPrivMsg::~cPrivMsg()
{}

void	cPrivMsg::toChannel(Client* client, std::string& target, Arguments& arguments)
{
	Channel*	channel_ptr = this->_server.getChannel(target.substr(1));

	if (!channel_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), target));

	if (!channel_ptr->isMember(client))
		return (void)client->queuePacket(ERR_CANNOTSENDTOCHAN(client->getNickname(), target));

	channel_ptr->sendMessage(RPL_PRIVMSG(client->getNickname(), target, arguments.getRemaining().substr(1)), client);
}

void	cPrivMsg::toClient(Client* client, std::string& target, Arguments& arguments)
{
	Client*		client_ptr = this->_server.getClient(target);

	if (!client_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), target));

	client_ptr->queuePacket(RPL_PRIVMSG(client->getNickname(), target, arguments.getRemaining().substr(1)));
}


void	cPrivMsg::Execute(Client* client, Arguments& arguments)
{
	std::string	target(arguments.popArgument());

	if (target[0] == '#')
		this->toChannel(client, target, arguments);
	else
		this->toClient(client, target, arguments);
}
