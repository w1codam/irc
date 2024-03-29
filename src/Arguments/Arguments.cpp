#include "Arguments.hpp"

Arguments::Arguments(std::string& packet)
{
	std::stringstream			ss(packet);
	std::string					part;

	while (ss >> part)
		this->_queue.push(part);
}

Arguments::~Arguments()
{}

std::string	Arguments::popArgument()
{
	if (!this->_queue.size())
		throw std::out_of_range("queue is empty");

	std::string	arg(this->_queue.front());	
	this->_queue.pop();

	// if (arg.size() == 1 && arg[0] == ':')
		// throw std::out_of_range("queue is empty");

	return arg;
}

std::string	Arguments::getRemaining()
{
	std::string	full;

	full = this->popArgument();
	while (this->_queue.size())
		full += " " + this->popArgument();

	return full;
}

size_t	Arguments::Size()
{
	return this->_queue.size();
}
