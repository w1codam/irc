#include "Channel.hpp"

Channel::Channel(std::string name, std::string password):
	_name(name),
	_password(password),
	_invite_only(false),
	_topic_ops_only(false),
	_user_limit(0)
{
}

Channel::~Channel()
{
	this->sendMessage("NOIMPL: bye :D");
}

void	Channel::sendMessage(std::string message, Client* ignore)
{
	std::vector<Client*>::iterator	it;

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		if (*it != ignore)
			(*it)->queuePacket(message);
		++it;
	}
}
