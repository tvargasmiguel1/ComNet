#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "HTTP_Server.h"
#include "Routes.h"
#include "Response.h"

int main() {
    HTTP_Server http_server;
    initializeServer(&http_server, 7227); // Initialize the server on port 7227

    // Registering Routes
    struct Route *route = initializeRoute("/", "demo.html");


    // Display all available routes
    printf("\n");
    printf("     Active ROUTES\n");
    inorder(route);

    while (1) {
        int client_socket = accept(http_server.socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Failed to accept client connection");
            continue;
        }

        char clientMessage[4096] = {0};
        int read_bytes = read(client_socket, clientMessage, sizeof(clientMessage) - 1);
        if (read_bytes < 0) {
            perror("Failed to read from client");
            close(client_socket);
            continue;
        }

        printf("Request:\n%s\n", clientMessage);

        char *method = strtok(clientMessage, " ");
        char *urlRoute = strtok(NULL, " ");
        if (!method || !urlRoute) {
            perror("Error parsing request");
            close(client_socket);
            continue;
        }

        printf("Method: %s\nRoute: %s\n", method, urlRoute);

        // Resolve the route to a template file
        char demo_path[256] = "../../ComNet/Demo/";
        struct Route *destination = strstr(urlRoute, "/static/") ? NULL : search(route, urlRoute);

        if (destination) {
            strcat(demo_path, destination->value);
        } else {
            strcpy(demo_path, "../../ComNet/Demo/404.html");
        }

        char *response_data = render_static_file(demo_path);
        if (!response_data) {
            perror("Failed to load template file");
            response_data = "<html><body><h1>500 Internal Server Error</h1></body></html>"; // Fallback error message
        }

        char http_header[4096];
        snprintf(http_header, sizeof(http_header), "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n%s", response_data);

        send(client_socket, http_header, strlen(http_header), 0);

        close(client_socket);
        free(response_data);
    }

    return 0;
}



