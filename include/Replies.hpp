#ifndef REPLIES_H
#define REPLIES_H

// RPL
#define RPL_WELCOME(nick)						"001 :Welcome " + nick

// 4xx (error)
#define ERR_UNKNOWNERROR(command)				"400 " + std::string(command) + ":Unknown error"
#define ERR_UNKNOWNCOMMAND(nick, command)		"421 " + nick + " " + command + " :Unknown command"
#define ERR_NICKNAMEINUSE(nick)					"433 " + nick + " " + nick  + " :Nickname is already in use by another user"
#define ERR_NOTREGISTERED(nick)					"451 " + nick + " :You are not registered yet"
#define ERR_NEEDMOREPARAMS(nick, command)		"461 " + nick + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nick)				"462 " + nick + " :You are already registered"
#define ERR_PASSWDMISMATCH(nick)				"464 " + nick + " :Incorrect password"


#endif