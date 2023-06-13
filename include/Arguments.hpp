#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <sstream>
#include <string>
#include <queue>

class Arguments
{
private:
	std::queue<std::string>	_queue;
public:
	Arguments(std::string& packet);
	~Arguments();

	std::string		popArgument();
};

#endif