#include <iostream>
#include "Networking.hpp"
#include "Server.hpp"

int	main(void)
{
	std::cout << "servin'" << std::endl;

	try
	{
		Server	server("6667", "passw");
		while (true) server.Serve();
	}
	catch (const std::exception &e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
