#include "Command.hpp"

Command::Command(Server& server, const bool authRequired):
	_authRequired(authRequired),
	_server(server)
{}

Command::~Command()
{}

bool	Command::authRequired()
{
	return this->_authRequired;
}

static std::string	getArgument(std::vector<std::string>& arguments)
{
	std::string	argument;

	argument = arguments.at(0);
	arguments.erase(arguments.begin());

	return argument;
}

static std::string	joinArguments(std::vector<std::string>& arguments)
{
	std::string	full;

	full = Command::getArgument(arguments);
	while (arguments.size())
		full += " " + Command::getArgument(arguments);
	
	return full;
}

