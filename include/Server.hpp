#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <map>

#include "Debug.hpp"
#include "CommandHandler.hpp"
#include "Networking.hpp"
#include "Client.hpp"

class CommandHandler;

class Server
{
private:
	int						_socket;
	const in_port_t			_port;
	const std::string		_password;
	const CommandHandler*	_commandHandler;

	std::vector<pollfd>		_pollfds;
	std::map<int, Client*>	_clients;
public:
	Server(std::string port, std::string password);
	~Server();

	void		Serve();							// main loop
	Client*		getClient(std::string nickname);	// does not throw
	bool		checkPassword(std::string password);
private:
	Client*		addClient(int fd);					// makes new client, set fd
	Client*		getClient(int fd);					// throws if the fd is not found in the map
	void		removeClient(int fd);				// this function should also remove the client from all channels

	void		addPoll(int fd, short events);		// functions to add to poll array, and set/remove flags (eg. POLLOUT)
	void		setPFlag(pollfd &pfd, short events);
	void		removePFlag(pollfd &pfd, short events);

	void		acceptClient();
	bool		handleData(Client* client);			// returns false if client should be removed
	void		processPackets(Client* client);
	void		handleDisconnect(Client* client);
};

#endif