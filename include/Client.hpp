#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "Networking.hpp"

class Client
{
private:
	int							_socket;

	std::vector<std::string>	_queue;
public:
	Client();
	~Client();

	void	setSocket(int fd);
	int		getSocket();

	/*
	 * processQueue() will try to send all outbound packets but
	 * in the case that the socket is not ready for sending yet
	 * 
	 * if no packets are left in the queue, it returns true
	 * else it returns false
	 */
	bool	processQueue();

	/*
	 * sendPacket() sends the current packet
	 * it basically does what processQueue does but for a single packet
	 * if no data could be sent while mid-packet, it truncates what has been sent
	 * 
	 * if the full packet has been transmitted, it returns true
	 * else it returns false
	 */
	bool	sendPacket();
};

#endif