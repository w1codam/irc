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

	if (arguments.Size())
		password = arguments.popArgument();

	channel_ptr = this->_server.getChannel(channel);
	if (!channel_ptr)
		channel_ptr = this->_server.addChannel(channel, password);
	
	if (channel_ptr->getUserLimit() && channel_ptr->getUserLimit() >= channel_ptr->Size())
		return (void)client->queuePacket("NOIMPL: channel is full");
	
	if (!channel_ptr->checkPassword(password))
		return (void)client->queuePacket(ERR_BADCHANNELKEY(client->getNickname(), channel));

	channel_ptr->addMember(client);
}
