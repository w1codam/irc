#include "Command.hpp"

cKick::cKick(Server& server):
	Command(server, true)
{}

cKick::~cKick()
{}

void	cKick::Execute(Client* client, Arguments& arguments)
{
	std::string	channel(arguments.popArgument());
	std::string	member(arguments.popArgument());

	Channel*	channel_ptr = this->_server.getChannel(channel.substr(1));
	Client*		member_ptr = this->_server.getClient(member);

	if (!channel_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));
	if (!member_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), member));
	if (channel_ptr->isOperator(member_ptr))
		return (void)client->queuePacket("NOIMPL: ur not op");
	
	channel_ptr->removeMember(member_ptr);
}
