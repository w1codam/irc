#include "Command.hpp"

cMode::cMode(Server& server):
	Command(server, true)
{}

cMode::~cMode()
{}

void	cMode::Execute(Client* client, Arguments& arguments)
{
	std::string				channel(arguments.popArgument());
	std::string				modes;
	char					mode;
	std::string::iterator	it;
	bool					add = true;

	Channel*	channel_ptr = this->_server.getChannel(channel.substr(1));

	if (!channel_ptr)
		return (void)client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), channel));

	if (!arguments.Size())
		return (void)client->queuePacket(RPL_MODE(client->getNickname(), channel, channel_ptr->getModes()));

	if (!channel_ptr->isOperator(client))
		return (void)client->queuePacket(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel));

	modes = arguments.popArgument();

	it = modes.begin();
	while (it != modes.end())
	{
		mode = *((it)++);
		switch (mode)
		{
		case '+': add = true;	break;
		case '-': add = false;	break;
		case 'i':
			if 	(add)	channel_ptr->setInviteOnly(true);
			else		channel_ptr->setInviteOnly(false);
			break;
		case 't':
			if 	(add)	channel_ptr->setTopicOpsOnly(true);
			else		channel_ptr->setTopicOpsOnly(false);
			break;
		case 'k':
			if (add)	channel_ptr->setPassword(arguments.popArgument());
			else		channel_ptr->setPassword("");
			break;
		case 'o':
		{
			std::string	nickname = arguments.popArgument();
			Client*		member = this->_server.getClient(nickname);
			if (!member)
			{
				client->queuePacket(ERR_NOSUCHNICK(client->getNickname(), nickname));
				break;
			}
			if (!channel_ptr->isMember(member))
			{
				client->queuePacket(ERR_NOTAMEMBER(client->getNickname(), nickname, channel));
				break;
			}
			if (add)	channel_ptr->addOperator(member);
			else		channel_ptr->removeOperator(member);
			break;
		}
		case 'l':
			if (add)	channel_ptr->setUserLimit(std::stoi(arguments.popArgument()));
			else		channel_ptr->setUserLimit(0);
			break;
		default: client->queuePacket(ERR_UNKNOWNMODE(client->getNickname(), mode, channel));
		}
	}

	channel_ptr->sendMessage(RPL_MODE(client->getNickname(), channel, channel_ptr->getModes()));
}
