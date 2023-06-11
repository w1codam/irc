#include "Command.hpp"

Command::Command(const Server& server, const bool authRequired):
	_server(server),
	_authRequired(authRequired)
{}

Command::~Command()
{}

