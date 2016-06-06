#define _CRT_SECURE_NO_WARNINGS
#include "server.hpp"

int main() {
	lib_init();
	socket_t * server = socket_new();
	socket_bind(server, 5678);
	socket_listen(server);
	json_t* players = json_array();
	
	char buf[10000];
	while (1) {
		socket_t * client = socket_accept(server);
		socket_read(client, buf, sizeof(buf));
		printf("%s", buf);
		server_request_t request = server_request_parse(buf);
		if (strcmp(request.method, "GET") == 0){
			if (strstr(request.uri, "/api/players/") != 0) {
				server_sendRawJson(client, players);
			}
		}
		else if (strcmp(request.method, "POST") == 0) {
			if (strcmp(request.uri, "/api/players/update") == 0) {
				// todo quotes on client-side!!!!
				server_updatePlayer(players, buf);
				server_sendHtml(client, "OK");
				puts(json_dumps(players, JSON_INDENT(3)));
			}
		}
		//else if
		socket_free(client);

	}
	socket_free(server);
	lib_free();



	return 0;
}

