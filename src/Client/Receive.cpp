#include "Client.hpp"

// since the eval sheet specified we should only call recv/send only ONCE
// even after checking errno (???????),
// change while to if and return if \r\n is present in the buffer
bool			Client::receivePacket()
{
	ssize_t	received;
	char	buffer[1024];

	if (this->_buffer.find("\r\n") == std::string::npos)
	{
		received = Networking::Recv(this->_socket, buffer, sizeof(buffer) - 1);

		if (received == -1 && errno == EAGAIN)
		{
			errno = 0;
			return false;
		}
		if (received == -1)
			throw Networking::NetworkingException("receivePacket() -> Recv() failure and errno != EAGAIN");
		if (received == 0)
			throw Networking::NetworkingException("receivePacket() peer disconnected");

		buffer[received] = '\0';
		this->_buffer += buffer;
	}

	return this->_buffer.find("\r\n") != std::string::npos;
}

// bool			Client::receivePacket()
// {
// 	ssize_t	received;
// 	char	buffer[1024];

// 	while (this->_buffer.find("\r\n") == std::string::npos)
// 	{
// 		received = Networking::Recv(this->_socket, buffer, sizeof(buffer) - 1);

// 		if (received == -1 && errno == EAGAIN)
// 		{
// 			errno = 0;
// 			return false;
// 		}
// 		if (received == -1)
// 			throw Networking::NetworkingException("receivePacket() -> Recv() failure and errno != EAGAIN");
// 		if (received == 0)
// 			throw Networking::NetworkingException("receivePacket() peer disconnected");

// 		buffer[received] = '\0';
// 		this->_buffer += buffer;
// 	}

// 	return true;
// }

std::string		Client::getPacket()
{
	size_t		pos;
	std::string	packet;

	pos = this->_buffer.find("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("getPacket() called without CRLF present in buffer");

	packet = this->_buffer.substr(0, pos);
	this->_buffer.erase(0, pos + 2);

	DEBUG(std::cout << "server <- [" << (this->getNickname().empty() ? "UNKNOWN" : this->getNickname()) << "] : " << packet << std::endl;)
	return packet;
}
