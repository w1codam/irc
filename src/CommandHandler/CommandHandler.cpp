#include "CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server):
	_server(server)
{
	this->_commands["NICK"] = new cNick(this->_server);
	this->_commands["USER"] = new cUser(this->_server);
	this->_commands["PASS"] = new cPass(this->_server);
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

Command*	CommandHandler::getCommand(std::string& command) const
{
	return this->_commands.at(command);
}

void	CommandHandler::Invoke(Client* client, std::string packet) const
{
	Arguments		args(packet);
	std::string		raw_command("NONE");
	Command*		command;

	try
	{
		raw_command = args.popArgument();
		command = this->getCommand(raw_command);

		if (command->authRequired() && client->Authenticated())
			return (void) client->queuePacket(ERR_UNKNOWNERROR("UNAUTHORIZED")); // NOIMPL : should return appropriate response

		try									{ command->Execute(client, args); }
		catch (const std::out_of_range& e)	{ client->queuePacket(ERR_NEEDMOREPARAMS(client->getNickname(), raw_command)); }
	}
	catch(const std::exception& e)
	{
		client->queuePacket(ERR_UNKNOWNCOMMAND(client->getNickname(), raw_command));
	}
}
