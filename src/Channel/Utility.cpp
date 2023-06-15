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

void		Channel::setUserLimit(size_t limit)
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

size_t		Channel::getUserLimit()
{
	return this->_user_limit;
}

bool		Channel::checkPassword(std::string password)
{
	return this->_password == password;
}

std::string	Channel::getModes()
{
	std::string	modes("+n");

	if (this->_invite_only)			modes += 'i';
	if (!this->_password.empty())	modes += 'k';
	if (this->_topic_ops_only)		modes += 't';
	if (this->_user_limit)			modes += 'l';

	return modes;
}
