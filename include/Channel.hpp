#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>

#include "Debug.hpp"
#include "Client.hpp"
#include "Networking.hpp"

class Channel
{
private:
	std::string				_name;
	std::vector<Client*>	_members;
	std::vector<Client*>	_operators;
public:
	void	sendMessage(std::string message);	// for each member, append this to queue

	void	addUser(Client* client);
	void	removeUser(Client* client);
};

#endif