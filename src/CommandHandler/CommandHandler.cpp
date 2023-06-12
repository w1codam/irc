#include "CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server):
	_server(server)
{
	(void)this->_server;
	// alloc/set all commands
	this->_commands["NICK"] = new cNick(this->_server);
}

CommandHandler::~CommandHandler()
{
	std::map<std::string, Command*>::iterator	it;

	it = this->_commands.begin();
	while (it != this->_commands.end())
	{
		delete it->second;
		++it;
	}
}

Command*					CommandHandler::getCommand(std::string& command) const
{
	return this->_commands.at(command);
}

std::vector<std::string>	CommandHandler::parseArguments(std::string& packet) const
{
	std::stringstream			ss(packet);
	std::vector<std::string>	arguments;
	std::string					part;

	while (ss >> part)
		arguments.push_back(part);

	return arguments;
}

void	CommandHandler::Invoke(Client* client, std::string packet) const
{
	DEBUG(std::cout << "CH client " << client->getSocket() << ": " << packet;)

	std::vector<std::string>	arguments;
	std::string					raw_command("NONE");
	Command*					command;

	arguments = this->parseArguments(packet);

	try
	{
		raw_command = arguments[0];
		command = this->getCommand(raw_command);
		arguments.erase(arguments.begin());

		// if (!client->Authenticated() && command->authRequired())
		// 	return (void)client->queuePacket(ERR_NOTREGISTERED(client->getNickname()));

		try									{ command->Execute(client, arguments); }
		catch (const std::out_of_range& e)	{ client->queuePacket(ERR_NEEDMOREPARAMS(client->getNickname(), raw_command)); }
	}
	catch(const std::exception& e)
	{
		client->queuePacket(ERR_UNKNOWNCOMMAND(client->getNickname(), raw_command));
	}
}
