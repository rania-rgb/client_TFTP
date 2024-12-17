TFTP Client en C
Description du Projet
Ce projet implémente un client TFTP (Trivial File Transfer Protocol) en langage C. Le programme permet de télécharger (GET) ou de téléverser (PUT) des fichiers à destination ou en provenance d'un serveur TFTP.

La communication est réalisée via des sockets UDP conformément à la spécification RFC 1350.
L'objectif est de créer un client capable d'effectuer les opérations de base de TFTP tout en intégrant une gestion simple des erreurs.

Fonctionnalités
1. Requête de Lecture (GET) - RRQ
Télécharge un fichier depuis un serveur TFTP.
Gère la réception des paquets DATA et l'envoi des accusés de réception (ACK).
2. Requête d'Écriture (PUT) - WRQ
Téléverse un fichier vers un serveur TFTP.
Envoie les paquets DATA au serveur et gère la réception des ACK.
3. Architecture Modulaire
Résolution d'adresse IP et port avec getaddrinfo.
Création et gestion des sockets UDP.
Communication conforme au protocole TFTP : gestion des paquets DATA, ACK, RRQ et WRQ.
Structure du Projet
Fichier	Description
main.c	Point d'entrée principal. Gère les arguments et appelle les fonctions GET/PUT.
getaddrinfo.c	Résout l'adresse IP et le port du serveur via la fonction getaddrinfo.
tftp_rrq.c	Implémente l’envoi de la requête RRQ (Read Request) et reçoit les paquets DATA.
tftp_wrq.c	Implémente l’envoi de la requête WRQ (Write Request) et envoie les paquets DATA.
create_socket.c	Crée et configure le socket UDP pour la communication avec le serveur.
tftp_ack.c	Gère l'envoi et la réception des paquets ACK.
