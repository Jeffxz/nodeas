#include "NPI.h"

int npi_socket(int in_domain, int in_type, int in_protocol)
{
	return socket(in_domain, in_type, in_protocol);
}

int npi_bind(int in_sock, const struct sockaddr *in_addr, socklen_t in_addrlen)
{
	return bind(in_sock, in_addr, in_addrlen);
}

int npi_listen(int in_sock, int in_backlog)
{
	return listen(in_sock, in_backlog);
}

int npi_accept(int in_sock, struct sockaddr * in_addr, socklen_t * in_addrlen)
{
	return accept(in_sock, in_addr, in_addrlen);
}

size_t npi_recv(int in_sock, void *in_buff, size_t in_len, int in_flags)
{
	return recv(in_sock, in_buff, in_len, in_flags);
}

size_t npi_send(int in_sock, const void *in_buff, size_t in_len, int in_flags)
{
	return send(in_sock, in_buff, in_len, in_flags);
}

int npi_close(int in_file)
{
	return close(in_file);
}

