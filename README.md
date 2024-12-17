# client_TFTP
#TFTP Client en C
#Description du Projet
Ce projet implémente un client TFTP (Trivial File Transfer Protocol) en langage C. Le programme permet de télécharger (GET) ou de téléverser (PUT) des fichiers à destination ou en provenance d'un serveur TFTP. La communication est réalisée via des sockets UDP conformément au RFC 1350.

L'objectif de ce projet est de créer un client capable d'effectuer les opérations de base de TFTP, tout en respectant les standards et en intégrant une gestion simple des erreurs.

#Fonctionnalités
Requête de Lecture (GET) - RRQ :

Permet de télécharger un fichier depuis un serveur TFTP.
Réception des paquets DATA du serveur et envoi des accusés de réception ACK.
Requête d'Écriture (PUT) - WRQ :

Permet de téléverser un fichier vers un serveur TFTP.
Envoi des blocs de données (paquets DATA) et gestion des ACK du serveur.

#Architecture modulaire :

Gestion de la résolution d'adresse IP et port avec getaddrinfo.
Création et gestion des sockets UDP.
Communication conforme au protocole TFTP (paquets DATA, ACK, RRQ, WRQ).
Structure du Projet
main.c : Point d'entrée principal. Gère les arguments en ligne de commande et appelle les fonctions appropriées pour GET ou PUT.
getaddrinfo.c : Résolution d'adresse serveur en utilisant la fonction getaddrinfo.
tftp_rrq.c : Implémente l’envoi de la requête de lecture (RRQ) et reçoit les paquets DATA.
tftp_wrq.c : Implémente l’envoi de la requête d’écriture (WRQ) et envoie les paquets DATA.
create_socket.c : Crée et configure le socket UDP.
tftp_ack.c : Gère l'envoi et la réception des paquets ACK.
