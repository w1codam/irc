#include <iostream>
#include "Networking.hpp"
#include "Server.hpp"


int	main(void)
{
	std::string kek("");

	kek += "\x41\x42\x43\x41\x02\x43\x00\x41\x42\x43\x41\x42\x43";

	std::cout << kek.size() << std::endl;
	std::cout << kek << std::endl;
}

// int	main2(void)
// {
// 	std::cout << "servin'" << std::endl;

// 	try
// 	{
// 		Server	server("6667", "passw");
// 		server.Serve();
// 	}
// 	catch (const std::exception &e)
// 	{
// 		std::cout << "error: " << e.what() << std::endl;
// 	}

// 	return (EXIT_SUCCESS);
// }
