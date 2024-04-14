#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "HTTP_Server.h"
#include "Routes.h"
#include "Response.h"

void setup_routes(struct Route **route) {
    *route = initializeRoute("/", "index.html");
    addRoute(*route, "/about", "about.html");
}

void display_routes(const struct Route *route) {
    printf("\n====================================\n");
    printf("=========ALL AVAILABLE ROUTES========\n");
    inorder(route);
}

int parse_request(int client_socket, char **method, char **urlRoute) {
    char clientMessage[4096] = {0};
    int read_bytes = read(client_socket, clientMessage, sizeof(clientMessage) - 1);
    if (read_bytes < 0) return -1;

    char *client_http_header = strtok(clientMessage, "\n");
    if (!client_http_header) return -1;

    *method = strtok(client_http_header, " ");
    *urlRoute = strtok(NULL, " ");
    if (!*method || !*urlRoute) return -1;

    return 0;
}

void handle_connection(int client_socket, const struct Route *route) {
    char *method, *urlRoute;
    if (parse_request(client_socket, &method, &urlRoute) == -1) {
        perror("Failed to parse HTTP request");
        return;
    }

    printf("The method is %s\n", method);
    printf("The route is %s\n", urlRoute);

    char template[256] = "templates/";
    const struct Route *destination = search(route, urlRoute);
    if (!destination) {
        strcat(template, "404.html");
    } else {
        strcat(template, destination->value);
    }

    char *response_data = render_static_file(template);
    if (!response_data) {
        perror("Failed to load template");
        return;
    }

    char http_header[4096] = "HTTP/1.1 200 OK\r\nContent-Type:

