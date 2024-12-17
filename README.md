# **TFTP Client en C**

## **Description du Projet**
Ce projet implémente un **client TFTP** (**Trivial File Transfer Protocol**) en langage **C**. Le programme permet de **télécharger** (**GET**) ou de **téléverser** (**PUT**) des fichiers depuis/vers un serveur TFTP, conformément au **RFC 1350**. La communication est réalisée via des **sockets UDP**.

L'objectif est de proposer un client simple, modulaire et robuste capable d'effectuer les opérations de base tout en respectant le protocole TFTP.

---

## **Fonctionnalités**

### 🔹 **Requête de Lecture (GET) - RRQ**
- Télécharge un fichier depuis un serveur TFTP.
- Réception des **paquets DATA** envoyés par le serveur.  
- Envoi des **ACK** pour confirmer chaque bloc reçu.

### 🔹 **Requête d'Écriture (PUT) - WRQ**
- Téléverse un fichier vers un serveur TFTP.
- Découpe le fichier local en **blocs de 512 octets**.  
- Envoie les **paquets DATA** et gère la réception des **ACK**.

### 🔹 **Architecture Simplifiée**
- **Résolution de l’adresse IP et port** ainsi que **création du socket UDP** directement dans `getaddrinfo.c`.  
- Communication TFTP conforme au **RFC 1350** avec gestion des paquets **DATA**, **ACK**, **RRQ** et **WRQ**.  
- Gestion des erreurs simples via des affichages d’erreur.

---

## **Structure du Projet**

| **Fichier**            | **Description**                                                             |
|------------------------|----------------------------------------------------------------------------|
| **`main.c`**           | Point d'entrée principal. Gère les arguments de la ligne de commande et appelle les opérations `GET` ou `PUT`. |
| **`getaddrinfo.c`**    | Résout l'adresse IP et le port avec `getaddrinfo`. Crée également le **socket UDP** pour la communication. |
| **`tftp_rrq.c`**       | Implémente l'envoi de la requête **RRQ** et gère la réception des **DATA**.    |
| **`tftp_wrq.c`**       | Implémente l'envoi de la requête **WRQ** et des blocs **DATA**.               |
| **`tftp_ack.c`**       | Gère l'envoi et la validation des **ACK** pour les paquets de données.        |

---


## **Compilation**

Pour compiler le projet:  
```bash
gcc -o tftp_client main.c getaddrinfo.c tftp_rrq.c tftp_wrq.c tftp_ack.c -Wall
