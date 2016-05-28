#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server_func.h"



// NOTE! NO C++ code here, ".cpp" and ".hpp" are only because of Jansson lib.

// NOTE! Compiling requires linking "jansson_d.lib" for Debug & "jansson.lib" for Release. If you have launched ".vcxproj", it is already linked.

// HTML Main page is on localhost:5000
// Data is taken from "scientists.json"
// DELETE and POST requests were tested with cURL.
// If you want to save the state of JSON after each server launch, uncomment 5 rows at the end of this file


int main() {
	lib_init();
	socket_t * server = socket_new();
	socket_bind(server, 5000);
	socket_listen(server);
	/*FILE* input = fopen("scientists.json", "r");

	json_error_t error;
	json_t* root = json_loadf(input, 0, &error);
	fclose(input);*/

	char buf[10000];
	while (1) {
		socket_t * client = socket_accept(server);
		socket_read(client, buf, sizeof(buf));
		printf("%s", buf);
		server_request_t request = server_request_parse(buf);
		if (strcmp(request.method, "GET") == 0){
			if (strcmp(request.uri, "/") == 0){
				server_sendHomepage(client);
			}
			
		}
		else if (strcmp(request.method, "DELETE") == 0){
			
		}
		else if (strcmp(request.method, "POST") == 0){
			
		}
		else if (strcmp(request.method, "KEEPALIVE") == 0){
			//just catching, doing nothing
		}
		else server_send405(client);
		socket_free(client);
		
	}
	socket_free(server);
	lib_free();



	return 0;
}