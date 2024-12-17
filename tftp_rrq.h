#ifndef TFTP_RRQ_H
#define TFTP_RRQ_H

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
// Fonction pour envoyer une requête RRQ (Read Request)
void send_rrq(int sockfd, struct addrinfo *server_addr, char *file_name);

// Fonction pour recevoir un fichier depuis le serveur TFTP
void receive_file(int sockfd, FILE *file, struct addrinfo *server_addr);

#endif /* TFTP_RRQ_H */
