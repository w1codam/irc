#include "Command.hpp"

cJoin::cJoin(Server& server):
	Command(server, true)
{}

cJoin::~cJoin()
{}

void	cJoin::Execute(Client* client, Arguments& arguments)
{
	std::string	channel(arguments.popArgument().substr(1));
	std::string	password;

	Channel*	channel_ptr;
	bool		is_new;

	if (arguments.Size())
		password = arguments.popArgument();

	channel_ptr = this->_server.getChannel(channel);
	is_new = !channel_ptr;
	if (!channel_ptr)
		channel_ptr = this->_server.addChannel(channel, password);
	
	if (channel_ptr->getUserLimit() && channel_ptr->getUserLimit() >= channel_ptr->Size())
		return (void)client->queuePacket("NOIMPL: channel is full");
	
	if (!channel_ptr->checkPassword(password))
		return (void)client->queuePacket(ERR_BADCHANNELKEY(client->getNickname(), channel));

	if (channel_ptr->isMember(client))
		return (void)client->queuePacket("NOIMPL: already a member");

	if (channel_ptr->getInviteOnly() && !channel_ptr->isInvited(client))
		return (void)client->queuePacket("NOIMPL: ur not invited");

	channel_ptr->addMember(client);
	if (is_new)
		channel_ptr->addOperator(client);
}
