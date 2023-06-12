#ifndef REPLIES_H
#define REPLIES_H

// 4xx (error)
#define ERR_UNKNOWNCOMMAND(user, command)		"421 " + user + " " + command + " :Unknown command"
#define ERR_NOTREGISTERED(user)					"451 " + user + " :You are not registered yet"
#define ERR_NEEDMOREPARAMS(user, command)		"461 " + user + " " + command + " :Not enough parameters"

#endif