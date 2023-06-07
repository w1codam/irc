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
		Networking::Bind(server, 5555);
		Networking::Listen(server, 1);

		client = Networking::Accept(server, &address);
		Networking::Send(client, "hello\n", 6);

		close(client);
		close(server);
	}
	catch (Networking::NetworkingException &e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
