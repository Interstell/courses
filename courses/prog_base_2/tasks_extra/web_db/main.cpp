#include "headers.hpp"

const char* dbName = "database.db";

int main(void){
	lib_init();
	socket_t * server = socket_new();
	socket_bind(server, 5000);
	socket_listen(server);
	database_t db = db_new();
	
	db_openDB(db, dbName);

	char** dbTableNames = (char**)malloc(MAX_TABLES_IN_DB * sizeof(char*));
	for (int i = 0; i < MAX_TABLES_IN_DB; i++){
		dbTableNames[i] = (char*)malloc(50 * sizeof(char));
	}
	db_setTableCount(db, db_getListOfTables(db, dbTableNames));
	db_fillTables(db, dbTableNames);
	char buf[100000];
	while (1) {
		socket_t * client = socket_accept(server);
		socket_read(client, buf, sizeof(buf));
		printf("%s", buf);
		server_request_t request = server_request_parse(buf);
		if (strcmp(request.method, "GET") == 0){
			if (strcmp(request.uri, "/") == 0){
				server_sendHomepage(client, db, (char*)dbName, dbTableNames, db_getTableCount(db));
			}
			else if (strcmp(request.uri, "/favicon.ico") == 0){
				server_file(client, "favicon.ico");
			}
			else{
				char tableName[100];
				sscanf(request.uri, "/%s", tableName);
				table_t table = db_getTableByName(db, tableName);
				if (table) server_sendTablepage(client, db, table);
				const char * filePath = strstr(request.uri, "/") + 1;
				if (file_exists(filePath)) {
					server_file(client, filePath);
				}
				else {
					server_send404(client);
				}
			}
		}
		else if (strcmp(request.method, "POST") == 0){
			if (strcmp(request.uri, "/new") == 0){
				char* queryPointer = strstr(buf, "\r\n\r\n") + strlen("\r\n\r\n");
				string tableName = server_addNewRecord(db, queryPointer);
				table_t table = db_getTableByName(db, (char*)tableName.c_str());
				if (table) server_sendTablepage(client, db, table);
			}
			else if (strcmp(request.uri, "/delete") == 0){
				char* queryPointer = strstr(buf, "\r\n\r\n") + strlen("\r\n\r\n");
				string tableName = server_deleteRecord(db, queryPointer);
				table_t table = db_getTableByName(db, (char*)tableName.c_str());
				if (table) server_sendTablepage(client, db, table);
			}
			else if (strcmp(request.uri, "/update") == 0){
				char* queryPointer = strstr(buf, "\r\n\r\n") + strlen("\r\n\r\n");
				string tableName = server_updateRecord(db, queryPointer);
				table_t table = db_getTableByName(db, (char*)tableName.c_str());
				if (table) server_sendTablepage(client, db, table);
			}
		}
		socket_free(client);
	}
	socket_free(server);
	lib_free();

	for (int i = 0; i < MAX_TABLES_IN_DB; i++){
		free(dbTableNames[i]);
	}
	free(dbTableNames);

	return 0;
}