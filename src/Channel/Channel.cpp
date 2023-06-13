#include "Channel.hpp"

Channel::Channel(std::string name, std::string password):
	_name(name),
	_password(password)
{}

Channel::~Channel()
{
	this->sendMessage("NOIMPL: bye :D");
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
