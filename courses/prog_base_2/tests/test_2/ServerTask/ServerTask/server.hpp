#pragma once
#define _CRT_SECURE_NO_WARNINGS
extern "C"{
#include "socket.h"
#include "CURL\include\curl\curl.h"
#include "fshelper.h"
}

#include <jansson\jansson.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct {
	char method[8];
	char uri[256];
} server_request_t;

#define ARG_NUM 10
#define ARG_LENGTH 100

server_request_t server_request_parse(char * request);
int server_sendJson(socket_t* socket, json_t* root);
server_request_t http_request_parse(const char * const request);
void server_sendHtml(socket_t* client, char* pageText);
void server_send404(socket_t * client);
void server_send405(socket_t * client);

json_t * server_getDataFromExternalServer(void);
void server_sendDirectoryContentAsHtml(socket_t * client, char* filesDirPath, char* dirName);
