#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>

#include "Debug.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Networking.hpp"

class Channel
{
private:
	std::string				_name;
	std::string				_topic;
	std::string				_password;

	std::vector<Client*>	_members;
	std::vector<Client*>	_operators;
	std::vector<Client*>	_invited;	// able to join if channel is invite only

	bool					_invite_only;
	bool					_topic_ops_only;
	size_t					_user_limit;
public:
	void		setTopic(std::string topic);
	void		setPassword(std::string password);
	void		setInviteOnly(bool mode);
	void		setTopicOpsOnly(bool mode);
	void		setUserLimit(size_t limit);

	std::string	getTopic();
	bool		getInviteOnly();
	bool		getTopicOpsOnly();
	size_t		getUserLimit();
	bool		checkPassword(std::string password);

	std::string	getModes();
public:
	Channel(std::string name, std::string password);
	~Channel();

	void		sendMessage(std::string message, Client* ignore = NULL);	// for each member, append this to queue

	bool		isMember(Client* client);
	bool		isOperator(Client* client);
	bool		isInvited(Client* client);

	void		addMember(Client* client);
	void		addOperator(Client* client);
	void		addInvited(Client* client);

	void		removeMember(Client* client);
	void		removeOperator(Client* client);
	void		removeInvited(Client* client);

	size_t		Size();
};

#endif