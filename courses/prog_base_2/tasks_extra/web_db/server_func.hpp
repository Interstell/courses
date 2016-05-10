#pragma once
#include "headers.hpp"

typedef struct {
	char method[8];
	char uri[256];
} server_request_t;

#define ARG_NUM 30
#define ARG_LENGTH 150

server_request_t server_request_parse(char * request);

void server_sendHtml(socket_t* client, char* pageText);
void server_send404(socket_t * client);

void server_sendHomepage(socket_t * client, database_t db, char* dbName, char* tableNames[], int tableCount);
void server_sendTablepage(socket_t * client, database_t db, table_t table);
void server_file(socket_t * client, const char * fileName);
std::string server_addNewRecord(database_t db, char* query);
std::string server_deleteRecord(database_t db, char* query); 
std::string server_updateRecord(database_t db, char* query);