#ifndef NETWORKING_H
#define NETWORKING_H

#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

/*
 * Networking wrapper
 * functions that shouldn't normally fail will throw 
 * exceptions (eg. socket(), bind(), setsockopt() etc...)
 * 
 * this excludes read/write calls since they easily "fail"
 * (eg. when a socket is closed or no data is available yet
 * on nonblocking sockets)
 */

/*
 * Exceptions
 */

namespace Networking
{

class NetworkingException: public std::exception {
private:
	const char	*_reason;
public: 
	NetworkingException(const char *reason): _reason(reason) {}
	const char *what() const throw() { return _reason; }
};

}

/*
 * Normalized structures
 */

namespace Networking
{


}

/*
 * noexcept functions
 * have not been able to add the noexcept keyword for some reason
 */

namespace Networking
{

ssize_t	Recv(int socket, void *buffer, size_t length);
ssize_t	Send(int socket, const void *buffer, size_t length);

}

namespace Networking
{

int		Socket();													// all sockets we make are ipv4 and stream, no need for args
int		Accept(int socket, sockaddr_in *address);
void	Bind(int socket, const sockaddr *address);
void	Setsockopt(int socket, int option_name, int option_value);
void	Fcntl(int socket, int cmd, int val); 						// NOT USED, fcntl originally has a variable length argument but we only use it for O_NONBLOCK, could also just be SetNonBlocking(...);
void	Listen(int socket, int backlog);

}

/*
 * ease of use functions
 * functions here omit the requirement of sending structs we'll do nothing with anyways
 */

namespace Networking
{

void	Bind(int socket, in_addr_t addr, in_port_t port);	// directly bind socket to port
void	Setnonblocking(int socket);							// use fnctl to set socket to nonblocking
void	Close(int &socket);									// close socket safely and set fd to -1 (to prevent closing stdin or stdout)

}

#endif