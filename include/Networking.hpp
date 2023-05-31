#ifndef NETWORKING_H
# define NETWORKING_H

# include <exception>
# include <sys/socket.h>
# include <sys/types.h>
# include <fcntl.h>

/*
 * Networking wrapper
 * functions that shouldn't normally fail will throw 
 * exceptions (eg. socket(), bind(), setsockopt() etc...)
 * 
 * this excludes read/write calls since they easily "fail"
 * (eg. when a socket is closed)
 */

/*
 * Exceptions
 */

namespace Networking
{

class NetworkingException: public std::exception {
private:
	char	*_reason;
public: 
	NetworkingException(char *reason): _reason(reason) {} 
	char *what() { return _reason; }
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
 */

namespace Networking
{

ssize_t	Recv(int socket, void *buffer, size_t length)		noexcept;
ssize_t	Send(int socket, const void *buffer, size_t length)	noexcept;

}

namespace Networking
{

int32_t	Socket();									// all sockets we make are ipv4 and stream, no need for args
int32_t	Bind(int socket, const struct sockaddr *address)
int32_t	Setsockopt(int socket, int option_name);
int32_t	Fcntl(int socket, int cmd, int val); 		// fcntl originally has a variable length argument but we only use it for O_NONBLOCK

}

#endif