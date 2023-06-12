#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <sstream>
#include <string>
#include <map>

#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Command.hpp"

class Server;
class Command;

class CommandHandler
{
private:
	Server&								_server;
	std::map<std::string, Command*>		_commands;
private:
	std::vector<std::string>			parseArguments(std::string& packet) const;
	Command*							getCommand(std::string& command) const;
public:
	CommandHandler(Server& server);
	~CommandHandler();

	void	Invoke(Client* client, std::string packet) const;
};

#endif