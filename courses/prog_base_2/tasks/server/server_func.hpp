#pragma once
#define _CRT_SECURE_NO_WARNINGS
extern "C"{
#include "socket.h"
}
#include "jansson\jansson.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char method[8];
	char uri[256];
} server_request_t;

#define ARG_NUM 10
#define ARG_LENGTH 100

server_request_t server_request_parse(char * request);
int server_sendJson(socket_t* socket, json_t* root);
server_request_t http_request_parse(const char * const request);
void server_sendHomepage(socket_t * client);
void server_send404(socket_t * client);
json_t* server_getScientistById(json_t* root, int scId);
void server_sendWrongIndexFormat(socket_t * client, char* wrongId);
void server_sendWrongIndex(socket_t * client, int wrongId);
void server_send405(socket_t * client);
json_t* server_deleteScientistById(json_t* root, int scId);
void server_sendHtml(socket_t* client, char* pageText);
int server_getCurrentFreeId(json_t* root);
json_t* server_createNewSc(json_t* root, char* query, int id);
void server_sendInputPage(socket_t* client);