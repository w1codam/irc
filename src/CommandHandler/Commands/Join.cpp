#include "Command.hpp"

cJoin::cJoin(Server& server):
	Command(server, true)
{}

cJoin::~cJoin()
{}

void	cJoin::Execute(Client* client, Arguments& arguments)
{
	std::string	channel(arguments.popArgument());
	std::string	password;

	Channel*	channel_ptr;
	bool		is_new;

	if (channel[0] != '#')
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));
	channel.erase(0, 1);

	if (arguments.Size())
		password = arguments.popArgument();

	channel_ptr = this->_server.getChannel(channel);
	is_new = !channel_ptr;
	if (!channel_ptr)
		channel_ptr = this->_server.addChannel(channel, password);
	
	if (channel_ptr->getUserLimit() && channel_ptr->getUserLimit() >= channel_ptr->Size())
		return (void)client->queuePacket(ERR_CHANNELISFULL(client->getNickname(), channel));
	
	if (!channel_ptr->checkPassword(password))
		return (void)client->queuePacket(ERR_BADCHANNELKEY(client->getNickname(), channel));

	if (channel_ptr->isMember(client))
		return (void)client->queuePacket(RPL_JOIN(client->getNickname(), channel));

	if (channel_ptr->getInviteOnly() && !channel_ptr->isInvited(client))
		return (void)client->queuePacket(ERR_INVITEONLY(client->getNickname(), channel));

	channel_ptr->addMember(client);
	if (is_new)
		channel_ptr->addOperator(client);
	channel_ptr->sendMessage(RPL_JOIN(client->getNickname(), channel));
}
