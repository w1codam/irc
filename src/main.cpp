#include <iostream>
#include "Networking.hpp"
#include "Server.hpp"

int	main(void)
{
	std::cout << "servin'" << std::endl;

	try
	{
		int	server, client;
		sockaddr_in address;

		server = Networking::Socket();
		Networking::Setnonblocking(server);
		Networking::Setsockopt(server, SO_REUSEPORT, 1);
		Networking::Bind(server, INADDR_ANY, 6667);
		Networking::Listen(server, 1);

		client = Networking::Accept(server, &address);
		Networking::Send(client, "hello\n", 6);

		Networking::Close(client);
		Networking::Close(server);
	}
	catch (const std::exception &e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
