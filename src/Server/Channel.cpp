#include "Server.hpp"

Channel*	Server::addChannel(std::string channel, std::string password)
{
	Channel*	new_channel;

	new_channel = new Channel(channel, password);
	this->_channels[channel] = new_channel;

	return new_channel;
}

Channel*	Server::getChannel(std::string channel)
{
	std::map<std::string, Channel*>::iterator	it;

	it = this->_channels.begin();
	while (it != this->_channels.end())
	{
		if (it->first == channel)
			return it->second;
		++it;
	}
	return NULL;
}

void	Server::removeChannel(std::string channel)
{
	std::map<std::string, Channel*>::iterator	it;

	it = this->_channels.find(channel);

	if (it == this->_channels.end())	// should never happen
		throw std::runtime_error("removeChannel() failure, client does not exist");

	delete it->second;
	this->_channels.erase(it);
}
