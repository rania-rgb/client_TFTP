#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "tftp_rrq.h"
#include <stdlib.h>

//Dans cette partie, on veut construire  et envoyer la requête RRQ pour demander le fichier au serveur. Dans le terminal j'ai demandé par ex zeros256,
//donc mon code va lire ce fichier déjà établi dans le serveur.

void send_rrq(int sockfd, struct addrinfo *server_addr, const char *file_name) {
    // Vérification des paramètres
    if (!server_addr || !server_addr->ai_addr || !file_name) {
        fprintf(stderr, "Erreur : Paramètres invalides (NULL)\n");
        return;
    }

    // ici, on crée un tableau buffer afin de stocker notre requête
    char buffer[512] = {0};  // Initialisation à zéro
    size_t len;

    // Construction de la requête RRQ
    len = snprintf(buffer, sizeof(buffer), "%c%c%s%c%s%c", 
                   0, 1,               // Opcode RRQ = 1 , qui s'occupe du 'GET' donc lecture
                   file_name, 0,       // Nom du fichier avec '\0'
                   "octet", 0);        // Mode "octet" avec '\0'

    // Vérification de la taille du message
    if (len <= 0 || len >= sizeof(buffer)) {
        fprintf(stderr, "Erreur : Requête RRQ trop grande\n");
        return;
    }

    // Envoi de la requête au serveur
    printf("Envoi de la requête RRQ pour le fichier : %s\n", file_name);
    ssize_t sent_bytes = sendto(sockfd, buffer, len, 0, server_addr->ai_addr, server_addr->ai_addrlen);
    // server_addr->ai_addr : C’est un pointeur vers la structure sockaddr contenant l'IP et le port
    if (sent_bytes < 0) {
        perror("Erreur lors de l'envoi de la requête RRQ avec sendto");
        exit(EXIT_FAILURE);
    }

    printf("Requête RRQ envoyée avec succès (%zd octets)\n", sent_bytes);
}
//ici, Cette fonction receive_file est responsable de recevoir un fichier depuis un serveur TFTP après l’envoi d’une requête RRQ (Read Request). 
//Elle gère le processus complet d'échange de paquets de données (DATA) et d’accusés de réception (ACK).
void receive_file(int sockfd, FILE *file, struct addrinfo *server_addr) {
    char buffer[516];
    int block = 1, n;

    while (1) {
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL); //reçevoir les paquets DATA
        fwrite(buffer + 4, 1, n - 4, file); //écrire les données reçues dans un fichier local

        // Envoyer ACK
        char ack[4] = {0, 4, buffer[2], buffer[3]};
        // Envoyer un paquet ACK pour confirmer la réception (avec sendto)
        sendto(sockfd, ack, 4, 0, server_addr->ai_addr, server_addr->ai_addrlen);
        // Vérifier le dernier bloc : Si le nombre d'octets reçus est inférieur à 516, c’est la fin du fichier
        if (n < 516) break;  // Dernier bloc
        block++;
    }
}
