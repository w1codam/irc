#include "Channel.hpp"

void		Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void		Channel::setPassword(std::string password)
{
	this->_password = password;
}

void		Channel::setInviteOnly(bool mode)
{
	this->_invite_only = mode;
}

void		Channel::setTopicOpsOnly(bool mode)
{
	this->_topic_ops_only = mode;
}

void		Channel::setUserLimit(uint32_t limit)
{
	this->_user_limit = limit;
}

std::string	Channel::getTopic()
{
	return this->_topic;
}

bool		Channel::getInviteOnly()
{
	return this->_invite_only;
}

bool		Channel::getTopicOpsOnly()
{
	return this->_topic_ops_only;
}

uint32_t	Channel::getUserLimit()
{
	return this->_user_limit;
}

bool		Channel::checkPassword(std::string password)
{
	return this->_password == password;
}
