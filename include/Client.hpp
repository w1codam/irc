#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <queue>

#include "Debug.hpp"
#include "Networking.hpp"

class Client
{
private: // irc related variables
	std::string					_nickname;
	std::string					_username;
	std::string					_realname;
	bool						_authenticated;
public:
	bool						Authenticated();
	std::string					getNickname();
	std::string					getUsername();
	std::string					getRealname();
	void						setNickname(std::string nickname);
	void						setUsername(std::string username);
	void						setRealname(std::string realname);
private:
	int							_socket;
	std::queue<std::string>		_queue;
	std::string					_buffer;
	sockaddr_in					_addr;
private:
	/*
	 * sendPacket() sends the current packet
	 * it basically does what processQueue does but for a single packet
	 * if no data could be sent while mid-packet, it truncates what has been sent
	 * 
	 * if the full packet has been transmitted, it returns true
	 * else it returns false
	 */
	bool	sendPacket();
public:
	Client();
	~Client();

	void			setSocket(int fd);
	int				getSocket();
	sockaddr_in&	getAddr();

	/*
	 * processQueue() will try to send all outbound packets but
	 * in the case that the socket is not ready for sending yet
	 * 
	 * if no packets are left in the queue, it returns true
	 * else it returns false
	 */
	bool	processQueue();
	void	queuePacket(std::string packet);	// simply append a packet to the queue
	size_t	getQueueSize();

	/*
	 * receivePacket() receives data from the socket until no more is available
	 * or until CRLF is found
	 * when CRLF is present, return true
	 * IMPORTANT: whenever receivePacket returns true, it means AT LEAST one packet is present in the buffer, could be more
	 * this is why getPacket should be called in a loop protected by a try/catch block and not just once
	 * a function processPackets could be implemented in the Server class which does this
	 */
	bool			receivePacket();
	std::string		getPacket();				// get packet until CLRF and keeps the rest in buffer, should only be called if CLRF is present
};

#endif