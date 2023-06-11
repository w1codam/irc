#include "CommandHandler.hpp"

CommandHandler::CommandHandler(const Server& server):
	_server(server)
{
	// alloc/set all commands
}

CommandHandler::~CommandHandler()
{
	std::map<std::string, Command*>::iterator	it;

	it = this->_commands.begin();
	while (it != this->_commands.end())
		delete it->second; ++it;
}

Command*					CommandHandler::getCommand(std::string& command) const
{
	return this->_commands.at(command);
}

std::vector<std::string>	CommandHandler::parseArguments(std::string& packet) const
{
	std::vector<std::string>	arguments;

	arguments.push_back(packet);

	return arguments;
}

void	CommandHandler::Invoke(Client* client, std::string packet) const
{
	DEBUG((void)this->_server;)
	DEBUG(std::cout << "CH client " << client->getSocket() << ": " << packet;)

	std::vector<std::string>	arguments;
	std::string					raw_command;
	Command*					command;

	arguments = this->parseArguments(packet);

	try
	{
		raw_command = arguments[0];
		command = this->getCommand(raw_command);
		arguments.erase(arguments.begin());
		command->Execute(client, arguments);
	}
	catch(const std::exception& e)
	{
		client->queuePacket(ERR_UNKNOWNCOMMAND(client->getNickname(), raw_command));
	}
}
