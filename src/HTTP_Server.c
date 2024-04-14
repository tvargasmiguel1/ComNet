#include "HTTP_Server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void initializeServer(HTTP_Server *http_server, int port) {
    if (http_server == NULL) {
        fprintf(stderr, "Error: HTTP server structure pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }

    http_server->port = port;

    // Create a socket for the server
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address structure
    struct sockaddr_in server_address = {0}; // Zero-initialize the structure
    server_address.sin_family = AF_INET; // Set address family to IPv4
    server_address.sin_port = htons(port); // Convert port number to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        close(server_socket); // Clean up the socket if binding fails
        exit(EXIT_FAILURE);
    }

    // Start listening on the socket with a queue limit for pending connections
    if (listen(server_socket, 5) == -1) {
        perror("Error starting to listen");
        close(server_socket); // Clean up the socket if listening setup fails
        exit(EXIT_FAILURE);
    }

    // Store the server socket in the HTTP server structure
    http_server->socket = server_socket;
    printf("HTTP Server initialized and running on port %d\n", http_server->port);
}
