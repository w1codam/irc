#include "Channel.hpp"

bool	Channel::isMember(Client* client)
{
	std::vector<Client*>::iterator	it;

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}

bool	Channel::isOperator(Client* client)
{

	std::vector<Client*>::iterator	it;

	it = this->_operators.begin();
	while (it != this->_operators.end())
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}

bool	Channel::isInvited(Client* client)
{

	std::vector<Client*>::iterator	it;

	it = this->_invited.begin();
	while (it != this->_invited.end())
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}

void	Channel::addMember(Client* client)
{
	if (this->isInvited(client))
		this->removeInvited(client);
	if (this->isMember(client))
		return;
	this->_members.push_back(client);
	client->queuePacket(RPL_JOIN(client->getNickname(), this->_name));
	client->queuePacket(RPL_MODE(client->getNickname(), this->_name, this->getModes()));
	client->queuePacket(RPL_TOPIC(client->getNickname(), this->_name, this->getTopic()));
}

void	Channel::addOperator(Client* client)
{
	if (this->isMember(client) && !this->isOperator(client))
		this->_operators.push_back(client);
}

void	Channel::addInvited(Client* client)
{
	if (!this->isMember(client) && !this->isInvited(client))
		this->_invited.push_back(client);
}

void	Channel::removeMember(Client* client)
{
	std::vector<Client*>::iterator	it;

	this->sendMessage(RPL_PART(client->getNickname(), std::string("#") + this->_name));

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		if (*it == client)	it = this->_members.erase(it);
		else				++it;
	}
}

void	Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator	it;

	it = this->_operators.begin();
	while (it != this->_operators.end())
	{
		if (*it == client)	it = this->_operators.erase(it);
		else				++it;
	}
}

void	Channel::removeInvited(Client* client)
{
	std::vector<Client*>::iterator	it;

	it = this->_invited.begin();
	while (it != this->_invited.end())
	{
		if (*it == client)	it = this->_invited.erase(it);
		else				++it;
	}
}

size_t	Channel::Size()
{
	return this->_members.size();
}
