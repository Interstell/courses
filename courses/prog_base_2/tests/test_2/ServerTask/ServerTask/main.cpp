#define _CRT_SECURE_NO_WARNINGS
#include "server.hpp"
#include "database.hpp"
extern "C"{
#include "list.h"
}

//ATTENTION! Server is on localhost:5000

//NO C++ CODE HERE! :)

void getFilesDirectory(char* exePath);

int main(int argc, char *argv[]) {
	lib_init();
	socket_t * server = socket_new();
	socket_bind(server, 5000);
	socket_listen(server);
	
	char filesDirPath[500];
	strcpy(filesDirPath, argv[0]);
	getFilesDirectory(filesDirPath);

	puts("\n\nATTENTION! Server is on localhost:5000\n\n");
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
				json_t* jsonArray = scientist_serializeListToJson(list);
				server_sendJson(client, jsonArray);
				list_free(list);
				db_delete(db);
			}
			else if (strstr(request.uri, "/dir/") != 0){
				char* dir = strstr(request.uri, "/dir/") + strlen("/dir/");
				server_sendDirectoryContentAsHtml(client, filesDirPath, dir);
			}
			else server_send404(client);

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

void getFilesDirectory(char* exePath){
	for (int i = strlen(exePath); i >= 0; i--){
		if (exePath[strlen(exePath) - 1] == '\\') break;
		exePath[strlen(exePath) - 1] = '\0';
	}
	strcat(exePath, "files\\");
}