#include "Client.hpp"

bool			Client::receivePacket()
{

}

std::string		Client::getPacket()
{
	size_t		pos;
	std::string	packet;

	pos = this->_buffer.find_first_of("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("getPacket() called without CRLF present in buffer");

	pos += 2; // include CRLF
	packet = this->_buffer.substr(0, pos);
	this->_buffer.erase(0, pos);

	return packet;
}
