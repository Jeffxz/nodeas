#ifndef NPI_H
#define NPI_H
#include "nodeassocket.h"

int npi_socket(int, int, int);
int npi_bind(int, const struct sockaddr *, socklen_t);
int npi_listen(int, int);
int npi_accept(int, struct sockaddr * __restrict, socklen_t * __restrict);
size_t npi_recv(int, void *, size_t, int);
size_t npi_send(int, const void *, size_t, int);
int npi_close(int);

#endif
