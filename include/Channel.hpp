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

	bool	isMember(Client* client);
	bool	isOperator(Client* client);

	void	addUser(Client* client);
	void	removeUser(Client* client);
	void	addOperator(Client* client);
	void	removeOperator(Client* client);
};

#endif