#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <errno.h>

#include "HTTP_Server.h" 
#include "Routes.h" 
#include "Response.h"

int main() {
    // Initialize HTTP_Server
    HTTP_Server http_server;
    initializeServer(&http_server, 6969); // Initialize the server on port 6969

    int client_socket;

    // Registering Routes
    struct Route *route = initializeRoute("/", "index.html"); // Initialize the root route
    addRoute(route, "/about", "about.html"); // Add the "/about" route

    printf("\n====================================\n");
    printf("=========ALL AVAILABLE ROUTES========\n");
    // Display all available routes
    inorder(route);

    while (1) { // Infinite loop to handle incoming client requests
        char clientMessage[4096] = ""; // Buffer to store client request

        // Accept client connection
        client_socket = accept(http_server.socket, NULL, NULL);

        // Read client request
        read(client_socket, clientMessage, 4095);

        // Print client request
        printf("%s\n", clientMessage);

        // Parsing client socket header to get HTTP method and route
        char *method = ""; // Variable to store HTTP method
        char *urlRoute = ""; // Variable to store requested route

        char *client_http_header = strtok(clientMessage, "\n"); // Tokenize client request header

        char *header_token = strtok(client_http_header, " "); // Tokenize header components
        int header_parse_counter = 0;

        while (header_token != NULL) { // Loop through header tokens
            switch (header_parse_counter) {
                case 0:
                    method = header_token; // Store HTTP method
                    break;
                case 1:
                    urlRoute = header_token; // Store requested route
                    break;
            }
            header_token = strtok(NULL, " "); // Move to next token
            header_parse_counter++;
        }

        // Print parsed HTTP method and route
        printf("The method is %s\n", method);
        printf("The route is %s\n", urlRoute);

        // Determine the template file based on the requested route
        char template[100] = ""; // Buffer to store template file path

        if (strstr(urlRoute, "/static/") != NULL) { // Check if route is for static content
            strcat(template, "static/index.css"); // Append static content path
        } else {
            // Search for route in registered routes
            struct Route *destination = search(route, urlRoute);
            strcat(template, "templates/"); // Append templates directory path

            if (destination == NULL) { // If route not found, use 404 template
                strcat(template, "404.html");
            } else {
                strcat(template, destination->value); // Use template associated with route
            }
        }

        // Render the template file into response data
        char *response_data = render_static_file(template);

        // Construct the HTTP response header
        char http_header[4096] = "HTTP/1.1 200 OK\r\n\r\n"; // HTTP response status line
        strcat(http_header, response_data); // Append response data
        strcat(http_header, "\r\n\r\n"); // Add empty line to terminate header

        // Send the HTTP response to the client
        send(client_socket, http_header, sizeof(http_header), 0);

        // Close the client socket
        close(client_socket);

        // Free dynamically allocated memory for response data
        free(response_data);
    }

    return 0;
}
