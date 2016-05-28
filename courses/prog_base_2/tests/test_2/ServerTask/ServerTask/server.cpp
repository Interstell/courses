#include "server.hpp"

typedef struct external_s{
	char author[100];
	char quote[500];
	time_t time;
} external_t;

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
		"HTTP/1.1 %s\n"
		"Content-Type: text/html\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"\n%s", (strstr(pageText, "404 NOT FOUND</title>") == NULL) ? "200 OK" : "404", strlen(pageText), pageText);
	socket_write_string(client, homeBuf);
	socket_close(client);
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
	strcpy((char*)stream, (char*)ptr);
	return size*count;
}

json_t * server_getDataFromExternalServer(void){
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	char resJSONChar[1000];

	curl_easy_setopt(curl, CURLOPT_URL, "http://pb-homework.appspot.com/test/var/25?format=json");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resJSONChar);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
	json_error_t error;
	json_t* serverJSON = json_loads(resJSONChar, 0, &error);
	time_t now = time(NULL);
	char buff[20];
	strftime(buff, 20, "%Y-%m-%d", localtime(&now));
	json_t* author = json_object_get(serverJSON, "author");
	json_t* quote = json_object_get(serverJSON, "quote");
	external_t extData;
	strcpy(extData.author, json_string_value(author));
	strcpy(extData.quote, json_string_value(quote));

	json_t* resJSON = json_pack("{s:s,s:s,s:s}", "author", extData.author, "quote", extData.quote, "time", buff);

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return resJSON;
}

void server_send404(socket_t * client) {
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "404 Not Found. The page or directory you are trying to reach is not found.");
	server_sendJson(client, error);
}

void server_send405(socket_t * client) {
	json_t* error = json_pack("{s:s,s:s}", "status", "ERROR", "description", "405 Method not allowed. You have no permission to modify this page");
	server_sendJson(client, error);
}

void server_sendDirectoryContentAsHtml(socket_t * client, char* filesDirPath, char* dirName){
	char pathToDir[500];
	sprintf(pathToDir, "%s%s", filesDirPath, dirName);
	if (dirName[0] == '\0'){
		pathToDir[strlen(pathToDir) - 1] = '\0';
	}
	if (!dir_exists(pathToDir)){
		server_send404(client);
		return;
	}
	if (dirName[0] == '\0'){
		strcpy(dirName, "%ROOT%");
	}
	char html[1000];
	char* htmlList = dir_getFilesAsHtmlList(pathToDir);
	sprintf(html, "<!DOCTYPE html><html><head><title>Directory: %s</title></head><body><h3 style=\"font-family:Verdana; color:red\">Files in directory %s: </h3>\n %s</body></html>", dirName, dirName, htmlList);
	server_sendHtml(client, html);
}
