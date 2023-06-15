#include <iostream>
#include "Networking.hpp"
#include "Server.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "usage: " << argv[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		Server	server(argv[1], argv[2]);

		std::cout << "servin' on :" << server.getPort() << std::endl;
		while (true) server.Serve();
	}
	catch (const std::exception &e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
