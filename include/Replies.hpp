#ifndef REPLIES_H
#define REPLIES_H

// RPL
#define RPL_WELCOME(origin)						"001 :Welcome " + origin
#define RPL_PRIVMSG(origin, target, message)	":" + origin + " PRIVMSG " + target + " :" + message
#define RPL_PART(origin, channel)				":" + origin + " PART :" + channel

// 4xx (error)
#define ERR_UNKNOWNERROR(command)				"400 " + std::string(command) + ":Unknown error"
#define ERR_NOSUCHNICK(origin, target)			"401 " + origin + " " + target + " :No such origin/channel"
#define ERR_CANNOTSENDTOCHAN(origin, channel)	"404 " + origin + " " + channel + " :You cannot sent messages to this channel"
#define ERR_UNKNOWNCOMMAND(origin, command)		"421 " + origin + " " + command + " :Unknown command"
#define ERR_NICKNAMEINUSE(origin)				"433 " + origin + " " + origin  + " :originname is already in use by another user"
#define ERR_NOTREGISTERED(origin)				"451 " + origin + " :You are not registered yet"
#define ERR_NEEDMOREPARAMS(origin, command)		"461 " + origin + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(origin)			"462 " + origin + " :You are already registered"
#define ERR_PASSWDMISMATCH(origin)				"464 " + origin + " :Incorrect password"
#define ERR_BADCHANNELKEY(origin, channel)		"475 " + origin + " #" + channel + " :Cannot join channel (+k)"

#endif