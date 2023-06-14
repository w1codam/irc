#include "Command.hpp"

cTopic::cTopic(Server& server):
	Command(server, true)
{}

cTopic::~cTopic()
{}

void	cTopic::Execute(Client* client, Arguments& arguments)
{
	std::string	channel(arguments.popArgument());
	std::string	topic;

	Channel*	channel_ptr = this->_server.getChannel(channel.substr(1));

	if (!channel_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));
	if (!arguments.Size())
		return (void)client->queuePacket(RPL_TOPIC(std::string("a channel operator"), channel, channel_ptr->getTopic()));
	
	topic = arguments.getRemaining();
	if (!channel_ptr->isOperator(client) && channel_ptr->getTopicOpsOnly())
		return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel));

	channel_ptr->setTopic(topic);
	channel_ptr->sendMessage(RPL_TOPIC(client->getNickname(), channel, topic));
}
