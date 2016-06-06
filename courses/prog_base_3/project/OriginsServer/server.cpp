#include "server.hpp"

int server_sendJson(socket_t* socket, json_t* root){
	char buffer[5000];
	char* jsonOutput = json_dumps(root, JSON_INDENT(3));
	sprintf(buffer,
		"HTTP/1.1 200 OK\n"
		"Content-Type: application/json\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"%s", strlen(jsonOutput), jsonOutput);
	socket_write_string(socket, buffer);
	return 1;
}

int server_sendRawJson(socket_t* socket, json_t* root) {
	char* jsonOutput = json_dumps(root, JSON_COMPACT);
	socket_write_string(socket, jsonOutput);
	return 1;
}

server_request_t server_request_parse(char * request) {
	server_request_t req;
	if (request[0] == '\0'){
		strcpy(req.method, "KEEPALIVE");
		strcpy(req.uri, "/");
		return req;
	}
	ptrdiff_t methodLen = strstr(request, " ") - request;
	memcpy(req.method, request, methodLen);
	req.method[methodLen] = '\0';
	const char * uriStartPtr = request + strlen(req.method) + 1;
	const char * uriEndPtr = strstr(uriStartPtr, " ");
	ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
	memcpy(req.uri, uriStartPtr, uriLen);
	req.uri[uriLen] = '\0';
	return req;
}

void server_sendHtml(socket_t* client, char* pageText){
	char homeBuf[1024];
	sprintf(homeBuf,
		"HTTP/1.1 %s\n"
		"Content-Type: text/html\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"\n%s", (strstr(pageText, "404 NOT FOUND</title>") == NULL) ? "200 OK" : "404", strlen(pageText) + 1, pageText);
	socket_write_string(client, homeBuf);
	socket_close(client);
}


void server_send404(socket_t * client) {
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "404 Not Found. The page or directory you are trying to reach is not found.");
	server_sendJson(client, error);
}

void server_updatePlayer(json_t* players, char* buf) {
	http_request_t request = http_request_parse(buf);
	char* jsonStr = (char*)http_request_getArg(&request, "json");
	json_error_t error;
	json_t* curPlayer = json_loads(jsonStr, 0, &error);
	json_t* jCurId = json_object_get(curPlayer, "id");
	int curId = json_integer_value(jCurId);
	for (int i = 0; i < json_array_size(players); i++) {
		json_t* player = json_array_get(players, i);
		json_t* id = json_object_get(player, "id");
		if (json_integer_value(id) == curId) {
			json_array_remove(players, i);
			break;
		}
	}
	json_array_append(players, curPlayer);
}
