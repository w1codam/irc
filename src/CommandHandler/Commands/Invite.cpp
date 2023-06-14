#include "Command.hpp"

cInvite::cInvite(Server& server):
	Command(server, true)
{}

cInvite::~cInvite()
{}

void	cInvite::Execute(Client* client, Arguments& arguments)
{
	std::string	member(arguments.popArgument());
	std::string	channel(arguments.popArgument());

	Client*		member_ptr = this->_server.getClient(member);
	Channel*	channel_ptr = this->_server.getChannel(channel.substr(1));

	if (!channel_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));
	if (!member_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), member));
	if (channel_ptr->getInviteOnly() && !channel_ptr->isOperator(client))
		return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel));

	channel_ptr->addInvited(member_ptr);
	member_ptr->queuePacket(RPL_INVITE(client->getNickname(), member, channel));
}
