#include "HTTP_Server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

// Initialize the HTTP server with the given port number
void init_server(HTTP_Server * http_server, int port) {
	http_server->port = port;

    // Create a socket for the server
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
	// Define the server address structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // Set address family to IPv4
    server_address.sin_port = htons(port); // Set port number and convert to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY; // Set the IP address to accept connections from any interface

    // Bind the socket to the server address
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5); // The second argument specifies the maximum number of pending connections

    // Store the server socket in the HTTP server structure
	http_server->socket = server_socket;
	printf("HTTP Server Initialized\nPort: %d\n", http_server->port);
}