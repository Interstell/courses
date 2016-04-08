#include "server_func.hpp"

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
		"HTTP/1.1 %d OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"\n%s", (strstr(pageText,"404 NOT FOUND</title>") == NULL)?200:404,strlen(pageText), pageText);
	socket_write_string(client, homeBuf);
	socket_close(client);
}

void server_sendHomepage(socket_t * client) {
	server_sendHtml(client, "<!DOCTYPE html><html><head><title>Scientists JSON Navigator</title></head><body><h1 style=\"color: green; font-family: Verdana\">Hello, Visitor!</h1><h3><p>To get the list of <i>scientists</i> go to <a href=\"/scientists\">/scientists</a></p></h3><h4>If you wanna look at the coolest <b><i>404</i></b> page ever, go <a href = \"/404\">here</a>. It is clickable.</h4><p style=\"font-size:70%\">(c)Urukov Dmitry KPI 2016</p></body></html>");
	
}

void server_send404(socket_t * client) {
	server_sendHtml(client, "<!DOCTYPE html><html><head><title>Scientists JSON Navigator| 404 NOT FOUND</title></head><body><iframe src=\"http://hotdot.pro/en/404/\" style=\"height:96vh; width:96vw\" >Here you must have seen a cool 404 page.Anyway, page not found.</iframe></body></html>");
}

void server_send405(socket_t * client) {
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "405 Method not allowed. You have no permission to modify this page");
	server_sendJson(client, error);
}

void server_sendWrongIndexFormat(socket_t * client, char* wrongId){
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "Wrong Id format.");
	server_sendJson(client, error);
}

void server_sendWrongIndex(socket_t * client, int wrongId){
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "Scientist with this Id does not exist");
	server_sendJson(client, error);
}

json_t* server_getScientistById(json_t* root, int scId){
	for (int i = 0; i < json_array_size(root); i++){
		json_t* sc = json_array_get(root, i);
		json_t* id = json_object_get(sc, "id");
		if (json_integer_value(id) == scId) return sc;
	}
	return NULL;
}

json_t* server_deleteScientistById(json_t* root, int scId){
	for (int i = 0; i < json_array_size(root); i++){
		json_t* sc = json_array_get(root, i);
		json_t* id = json_object_get(sc, "id");
		if (json_integer_value(id) == scId){
			json_t* scCopy = json_deep_copy(sc);
			json_t* response = json_pack("{s:s, s:o}", "status", "OK", "scientist", scCopy);
			json_array_remove(root, i);
			return response;
		}
	}
	json_t* notFound = json_pack("{s:s,s:s}", "status", "ERROR", "description", "Scientist with this Id does not exist");
	return notFound;
}

int server_getCurrentFreeId(json_t* root){
	int max = 0;
	for (int i = 0; i < json_array_size(root); i++){
		json_t* sc = json_array_get(root, i);
		json_t* id = json_object_get(sc, "id");
		if (json_integer_value(id) > max)
			max = json_integer_value(id);
	}
	return max + 1;
}

json_t* server_createNewSc(json_t* root, char* query, int id){
	json_t* newSc = json_pack("{s:i, s:s, s:s, s:s, s:s, s:s, s:s, s:s, s:f, s:i}", "id", id, "firstName", "", "surname", "", "fathersName", "", "birthDate", "", "domain", "", "degree", "", "thesis", "", "qIndex", 0.0, "patents", 0);
	char* queries[ARG_NUM];
	for (int i = 0; i < ARG_NUM; i++){
		queries[i] = (char*)malloc(ARG_LENGTH*sizeof(char));
	}
	char * pch = strtok(query, "&");
	int argCount = 0;
	while (pch != NULL){
		strcpy(queries[argCount++], pch);
		pch = strtok(NULL, "&");
		if (argCount > ARG_NUM) break;
	}
	int argsFilled = 0;
	for (int i = 0; i < argCount; i++){
		char argName[ARG_LENGTH / 2];
		char argVal[ARG_LENGTH / 2];
		char* argValPointer = strstr(queries[i], "=");
		if (NULL == argValPointer) return NULL;
		strcpy(argName, queries[i]);
		argName[argValPointer - queries[i]] = '\0';
		strcpy(argVal, argValPointer + 1);
		if (strcmp(argName, "firstName") == 0){
			json_object_set(newSc, "firstName", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "surname") == 0){
			json_object_set(newSc, "surname", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "fathersName") == 0){
			json_object_set(newSc, "fathersName", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "birthDate") == 0){
			json_object_set(newSc, "birthDate", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "domain") == 0){
			json_object_set(newSc, "domain", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "degree") == 0){
			json_object_set(newSc, "degree", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "thesis") == 0){
			json_object_set(newSc, "thesis", json_string(argVal));
			argsFilled++;
		}
		else if (strcmp(argName, "qIndex") == 0){
			char* end;
			double index = strtod(argVal, &end);
			if (index == HUGE_VAL || index == -HUGE_VAL || index == 0.0){
				json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "Wrong format of @qIndex. Scientist was NOT created");
				return error;
			};
			json_object_set(newSc, "qIndex", json_real(index));
			argsFilled++;
		}
		else if (strcmp(argName, "patents") == 0){
			char* end;
			long long patents = strtol(argVal, &end, 10);
			if (patents == LONG_MAX || patents == LONG_MIN || (patents == 0 && strcmp(argVal, "0") != 0)){
				json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "Wrong format of @patents. Scientist was NOT created");
				return error;
			}
			json_object_set(newSc, "patents", json_integer(patents));
			argsFilled++;
		}
	}
	if (argCount == 0 || argsFilled == 0){
		json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "No valuable parameters in query. Scientist was NOT created.");
		return error;
	}
	json_array_append(root, newSc);
	return newSc;
}