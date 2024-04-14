#include "HTTP_Server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

// Function to initialize the HTTP server on a given port
void initializeServer(HTTP_Server *http_server, int port) {
    if (!http_server) {
        fprintf(stderr, "Server structure is NULL\n");
        return;
    }

    http_server->port = port;

    // Create a socket for the server
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address structure
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address)); // Zero out structure
    server_address.sin_family = AF_INET; // Set address family to IPv4
    server_address.sin_port = htons(port); // Set port number (converted to network byte order)
    server_address.sin_addr.s_addr = INADDR_ANY; // Set the IP address to accept connections from any interface

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Failed to bind");
        close(server_socket); // Close socket to release resources
        exit(EXIT_FAILURE);
    }

    // Start listening on the socket with a maximum of 5 pending connections
    if (listen(server_socket, 5) == -1) {
        perror("Failed to listen on socket");
        close(server_socket); // Close socket to release resources
        exit(EXIT_FAILURE);
    }

    // Store the server socket in the HTTP server structure
    http_server->socket = server_socket;
    printf("HTTP Server initialized on port %d\n", http_server->port);
}

