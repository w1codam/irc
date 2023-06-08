#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <map>

#include "Networking.hpp"
#include "Client.hpp"

class Server
{
private:
	const in_port_t			_port;
	const std::string		_password;

	int						_socket;

	std::vector<pollfd>		_pollfds;
	std::map<int, Client*>	_clients;
public:
	Server(std::string port, std::string password);
	~Server();

	void		Serve();					// main loop

private:
	Client*		addClient(int fd);			// makes new client, set fd
	Client*		getClient(int fd);			// throws if the fd is not found in the map
	void		removeClient(int fd);		// this function should also remove the client from all channels

	void		addPoll(int fd, short events);
	void		setPFlag(pollfd &pfd, short events);		// when outbound messages need to be sent, we set POLL_OUT and remove it after the queue is empty
	void		removePFlag(pollfd &pfd, short events);		// only problem is; how do we set POLL_OUT from the client/channel classes? maybe give a reference 
															// to the pollfd struct?
															// OR WE USE client->hasQueue() to check if they have a queue :>
															// at the end of the poll loop ^

/*
to safely remove from poll vector while iterating

vector< string >::iterator it = curFiles.begin();
while(it != curFiles.end()) {
    if(aConditionIsMet)
        it = curFiles.erase(it);
    else ++it;
}

or use index based loops
*/

	void		acceptClient();
	void		handleDisconnect(int fd);
	void		handleData(int fd);
};

#endif