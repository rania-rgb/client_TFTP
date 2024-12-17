#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//on crée une fonction afin de récuperer l'adressse du serveur
//Ici, on utilise l'adresse 127.0.0.1 qui est une fonction loopback qui représente mon propre pc. Le port 1069 est celui où  mon serveur TFTP "écoute"
//getaddrinfo prend l'adresse IP et le port et retourne la structure addrinfo, qui va nous fournir toutes les infos. Pourquoi?
//les fonctions qu'on utilisera comme sendto, recvfrom etc ne comprennent pas ce que c'est "127.0.0.1", elles exigent une structure sockaddr
//contenant les informations en binaire. getaddrinfo permet d'éviter ce travail manuel de conversion.
struct addrinfo *get_server_address(char *server_ip, char *port) {
    struct addrinfo hints, *res;
    //Initialisation de la structure hints
    memset(&hints, 0, sizeof(hints)); //Initialisation de hints à 0
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_DGRAM; //Utilise UDP
    //Appel à getaddrinfo pour résoudre l'IP et le port
    int status = getaddrinfo(server_ip, port, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "Erreur getaddrinfo: %s\n", gai_strerror(status));
        return NULL;
    }
    return res; //Le pointeur res pointe vers la structure contenant l'adresse du serveur prête à être utilisée.
}
//On crée une fonction socket UDP. Pourquoi? 
//Le socket permet au d’envoyer des requêtes (RRQ, WRQ dans TFTP) et de recevoir des réponses (ACK, DATA). On le fait avec UDP. Comment ça se passe et pourquoi ce choix?
//UDP est un protocole non connecté :
//Aucune connexion n’est établie entre le client et le serveur.
//Chaque paquet envoyé contient toutes les informations nécessaires (IP + port source et destination).
//Lorsque le serveur reçoit un paquet, il utilise l’adresse source pour répondre directement
//Cela est parfait et compatible avec TFTP qui gère des packets simples.
//Le socket est simplement un canal d’envoi/réception qui transmet les paquets directement.
int create_socket() {
    int sockfd;

    // Création du socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //Donc ici on spécifie les arguments du socket qu'on veut, AF_INET étant IPv4 et SOCK_DRAM l'UDP, 
    //déjà précisés dans le code d'avant. 0 fait réference au protocole utilisé par défaut
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
    return sockfd; 
    //que retourne le socket?
    //socket retourne un descripteur de fichier : un entier positif
    //Ce descripteur est utilisé dans toutes les fonctions réseau suivantes (sendto, recvfrom, etc.) pour identifier le socket.
}