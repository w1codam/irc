#include "Client.hpp"

size_t	Client::getQueueSize()
{
	return this->_queue.size();
}

bool	Client::processQueue()
{
	while (this->_queue.size() && this->sendPacket());			// try to process all packets
	return this->_queue.size() == 0;
}

// bool	Client::sendPacket()
// {
// 	ssize_t			sent;
// 	std::string&	packet = this->_queue.front();

// 	while (packet.size())
// 	{
// 		sent = Networking::Send(this->_socket, packet.data(), packet.length());

// 		if ((sent == -1 && errno == EAGAIN) || sent == 0)	// send should not return 0 but it could? https://stackoverflow.com/questions/3081952/with-c-tcp-sockets-can-send-return-zero
// 		{
// 			errno = 0;
// 			return false;
// 		}
// 		if (sent == -1)
// 			throw Networking::NetworkingException("sendPacket() -> Send() failure and errno != EAGAIN");

// 		packet.erase(0, sent);
// 	}

// 	this->_queue.pop();
// 	return true;
// }

bool	Client::sendPacket()
{
	ssize_t			sent;
	std::string&	packet = this->_queue.front();

	if (packet.size())
	{
		sent = Networking::Send(this->_socket, packet.data(), packet.length());

		if ((sent == -1 && errno == EAGAIN) || sent == 0)	// send should not return 0 but it could? https://stackoverflow.com/questions/3081952/with-c-tcp-sockets-can-send-return-zero
		{
			errno = 0;
			return false;
		}
		if (sent == -1)
			throw Networking::NetworkingException("sendPacket() -> Send() failure and errno != EAGAIN");

		packet.erase(0, sent);
	}

	if (packet.size())
		return false;

	this->_queue.pop();
	return true;
}

void	Client::queuePacket(std::string packet)
{
	DEBUG(std::cout << "server -> [" << (this->getNickname().empty() ? "UNKNOWN" : this->getNickname()) << "] : " << packet << std::endl;)
	std::string	complete(packet + "\r\n");
	this->_queue.push(complete);
}
