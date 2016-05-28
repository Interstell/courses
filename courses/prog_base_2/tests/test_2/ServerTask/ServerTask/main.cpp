#define _CRT_SECURE_NO_WARNINGS
#include "server.hpp"
#include "database.hpp"

//NO C++ CODE HERE! :)

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
			if (strcmp(request.uri, "/info") == 0){
				server_sendJson(client, json_pack("{s:s,s:s,s:i}", "student", "Dmitry Urukov", "group", "KP-52", "variant", 25));
			}
			else if (strcmp(request.uri, "/external") == 0){
				json_t * externalInfo = server_getDataFromExternalServer();
				server_sendJson(client, externalInfo);
			}
			else if (strcmp(request.uri, "/database") == 0){
				database_t db = db_new();
				db_openDB(db, "database.db");
				list_t* list = db_getListOfScientistsFromDb(db);
				
				db_delete(db);
			}

		}
		else if (strcmp(request.method, "DELETE") == 0){

		}
		else if (strcmp(request.method, "POST") == 0){

		}
		else if (strcmp(request.method, "KEEPALIVE") == 0){
			//just catching, doing nothing
		}
		//else server_send405(client);
		socket_free(client);

	}
	socket_free(server);
	lib_free();



	return 0;
}