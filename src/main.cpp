#include <iostream>
#include "Networking.hpp"
#include "Server.hpp"


int	main(void)
{
	std::queue<std::string>	test;

	test.push("hello :)");

	test.front()[2] = 'X';

	std::string &s = test.front();

	std::cout << s << std::endl;
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
