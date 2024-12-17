#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tftp_rrq.h"
#include "tftp_wrq.h"
#include "getaddrinfo.h"


int main(int argc, char *argv[]) {
    //Afin de gérer le nombre d'arguments écrits dans le terminal
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <server_ip> <port> <file_name> <operation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *server_ip = argv[1];
    char *port = argv[2];
    char *file_name = argv[3];
    char *operation = argv[4];

    struct addrinfo *server_addr = get_server_address(server_ip, port);
    int sockfd = create_socket();
      // Vérification de l'opération demandée : "get" ou "put"
    if (strcmp(operation, "get") == 0) { //On compare entre l'opération demandée dans le terminal et get, si c 0 donc c effectivement qu'on demande
        FILE *file = fopen(file_name, "wb");
        if (!file) {
            perror("Erreur d'ouverture du fichier local");
            return EXIT_FAILURE;
        }
        // Si l'opération est "get", on appelle send_rrq pour une lecture
        send_rrq(sockfd, server_addr, file_name);
        receive_file(sockfd, file, server_addr);
        fclose(file);
    }
