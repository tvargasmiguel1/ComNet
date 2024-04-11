#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

//Creates the HTTP server represented as a struct class
typedef struct HTTP_Server {
	int socket; //will descript the socket for the server
	int port; //defines the port working in 	
} HTTP_Server;

//function call to initalize the server
void init_server(HTTP_Server* http_server, int port);

#endif