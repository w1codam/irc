#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <queue>

#include "Networking.hpp"

class Client
{
private:
	int							_socket;

	std::queue<std::string>		_queue;
	std::string					_buffer;
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
	void	queuePacket(std::string packet);	// simply append a packet to the queue
	size_t	getQueueSize();

	/*
	 * receivePacket() receives data from the socket until no more is available
	 * or until CRLF is found
	 * when CRLF is present, return true
	 */
	bool			receivePacket();
	std::string		getPacket();				// get packet until CLRF and keeps the rest in buffer, should only be called if CLRF is present
};

#endif