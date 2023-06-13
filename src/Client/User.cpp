#include "Client.hpp"

bool		Client::Authenticated()
{
	return this->_authenticated;
}

std::string	Client::getNickname()
{
	return this->_nickname;
}

std::string	Client::getUsername()
{
	return this->_username;
}

std::string	Client::getRealname()
{
	return this->_realname;
}

std::string	Client::getServerPassword()
{
	return this->_server_password;
}

void		Client::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void		Client::setUsername(std::string username)
{
	this->_username = username;
}

void		Client::setRealname(std::string realname)
{
	this->_realname = realname;
}

void		Client::setServerPassword(std::string password)
{
	this->_server_password = password;
}

void		Client::setAuthenticated()
{
	this->_authenticated = true;
}
