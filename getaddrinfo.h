#ifndef GETADDRINFO_H
#define GETADDRINFO_H

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

// Fonction pour obtenir l'adresse IP et le port via getaddrinfo
struct addrinfo *get_server_address(const char *server_ip, const char *port);

// Fonction pour créer un socket UDP
int create_socket();

#endif /* GETADDRINFO_H */

