#include "Channel.hpp"

Channel::Channel(std::string name, std::string password):
	_name(name),
	_topic("no topic set"),
	_password(password),
	_invite_only(false),
	_topic_ops_only(false),
	_user_limit(0)
{
}

Channel::~Channel()
{
	std::vector<Client*>::iterator	it;

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		this->sendMessage(RPL_PART((*it)->getNickname(), std::string("#") + this->_name));
		++it;
	}
}

void	Channel::sendMessage(std::string message)
{
	std::vector<Client*>::iterator	it;

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		(*it)->queuePacket(message);
		++it;
	}
}
