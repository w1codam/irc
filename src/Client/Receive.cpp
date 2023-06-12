#include "Client.hpp"

bool			Client::receivePacket()
{
	ssize_t	received;
	char	buffer[1024];	// pretty sure max length for a single packet is 512 bytes but lets see (513 to set the null-byte)

	while (this->_buffer.find("\r\n") == std::string::npos)
	{
		received = Networking::Recv(this->_socket, buffer, sizeof(buffer) - 1);

		if (received == -1 && errno == EAGAIN)
			return false;
		if (received == -1)
			throw Networking::NetworkingException("receivePacket() -> Recv() failure and errno != EAGAIN");
		if (received == 0) // peer disconnect, no idea what we do here, for now throw an exception
			throw Networking::NetworkingException("receivePacket() peer disconnected");

		buffer[received] = '\0';
		this->_buffer += buffer;
	}

	return true;
}

// FIX!!!
std::string		Client::getPacket()
{
	size_t		pos;
	std::string	packet;

	pos = this->_buffer.find("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("getPacket() called without CRLF present in buffer");

	packet = this->_buffer.substr(0, pos);
	this->_buffer.erase(0, pos + 2);

	DEBUG(std::cout << "server <- [" << this->getNickname() << "] : " << packet << std::endl;)
	return packet;
}
