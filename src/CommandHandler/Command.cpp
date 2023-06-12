#include "Command.hpp"

Command::Command(const Server& server, const bool authRequired):
	_authRequired(authRequired),
	_server(server)
{}

Command::~Command()
{}

bool	Command::authRequired()
{
	return this->_authRequired;
}
