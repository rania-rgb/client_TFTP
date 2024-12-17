#ifndef TFTP_UTILS_H
#define TFTP_UTILS_H

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
// Fonction pour obtenir l'adresse du serveur à partir d'une IP et d'un port
struct addrinfo *get_server_address(char *server_ip, char *port);

// Fonction pour créer un socket UDP
int create_socket();

#endif /* TFTP_UTILS_H */
