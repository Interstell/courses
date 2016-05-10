#include "headers.hpp"

using namespace std; 

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
	char homeBuf[100000];
	sprintf(homeBuf,
		"HTTP/1.1 %s\n"
		"Content-Type: text/html\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"\n%s", (strstr(pageText, "404 NOT FOUND</title>") == NULL) ? "200 OK" : "404", strlen(pageText) + 1, pageText);
	socket_write_string(client, homeBuf);
	socket_close(client);
}

static void replaceByTemplate(string& text, string template_key, string template_value){
	int pos = text.find(template_key);
	text.replace(pos, template_key.length(), template_value);
}

void server_sendHomepage(socket_t * client, database_t db, char* dbName, char* tableNames[], int tableCount){
	FILE* fIndex = fopen("index.html", "r");
	char buffer[1000];
	int end = fread(buffer, sizeof(char), 1000, fIndex);
	fclose(fIndex);
	buffer[end] = '\0';
	string html(buffer);
	string dbFilename(dbName);
	replaceByTemplate(html, "{{database_filename}}", dbFilename);
	string list;
	for (int i = 0; i < tableCount; i++){
		string li(tableNames[i]);
		list += "\t<a href = \"/" + li + "\"><li style=\"font-family:Verdana;font-size: 14pt;\">" + li + "</li></a>\n";
	}
	replaceByTemplate(html, "{{list}}", list);
	server_sendHtml(client, (char*)html.c_str());
}

void server_send404(socket_t * client) {
	server_sendHtml(client, "<!DOCTYPE html><html><head><title>404 NOT FOUND | Database Web Client</title></head><body><iframe src=\"http://hotdot.pro/en/404/\" style=\"height:96vh; width:96vw\" >Here you must have seen a cool 404 page.Anyway, page not found.</iframe></body></html>");
}

void server_sendTablepage(socket_t * client, database_t db, table_t table){
	int currentStatus = db->status;
	FILE* fTable = fopen("table.html", "r");
	char buffer[10000];
	int end = fread(buffer, sizeof(char), 10000, fTable);
	fclose(fTable);
	buffer[end] = '\0';
	string html(buffer);
	string tableName(table->name);
	replaceByTemplate(html, "{{table_title}}", tableName);
	replaceByTemplate(html, "{{table_name}}", tableName);
	string headers;
	for (int i = 0; i < table->columnsCount; i++){
		string heading(table->headings[i]);
		headers += "\t<th id=\"heading_"+heading+"\">" + heading + "</th>\n";
	}
	headers += "\t<th colspan=\"2\"><a href=\"javascript:create(); \"><img align=\"center\" id=\"add_btn\" src=\"images/add.png\"></a></th>";
	replaceByTemplate(html, "{{headers}}", headers);
	replaceByTemplate(html, "{{rows}}", table_getHtmlTableContent(table, db));
	db->status = currentStatus;
	replaceByTemplate(html, "{{inputs}}", table_getInputs(table));
	replaceByTemplate(html, "{{table_name_hidden}}", tableName);
	replaceByTemplate(html, "{{columns_num}}", to_string(table->columnsCount));
	replaceByTemplate(html, "{{last_id}}", table->lastId);
	string status;
	string statusType;
	string statusDesc;
	switch (db->status){
	case DB_INSERT_OK:
	case DB_UPDATE_OK:
	case DB_DELETE_OK:
		statusType.append("status_block_ok");
		break;
	case DB_ERROR:
	case DB_TYPE_MISMATCH:
	case DB_NOT_UNIQUE:
		statusType.append("status_block_error");
		break;
	}
	switch (db->status){
	case DB_INSERT_OK:
		statusDesc.append("New record created successfully.");
		break;
	case DB_UPDATE_OK:
		statusDesc.append("Record updated successfully.");
		break;
	case DB_DELETE_OK:
		statusDesc.append("Record deleted successfully.");
		break;
	case DB_ERROR:
		statusDesc.append("Database error occured. Try again.");
		break;
	case DB_TYPE_MISMATCH:
		statusDesc.append("Arguments type mismatch.<br> Check your input.");
		break;
	case DB_NOT_UNIQUE:
		statusDesc.append("Key field is not unique<br>for this table.");
		break;
	}
	status += "<div id=\""+statusType+"\"><div id = \"status_img\"></div><div id = \"status_text\">"+statusDesc+"</div></div>";
	if (db->status != DB_OK){
		replaceByTemplate(html, "{{status}}", status);
		db->status = DB_OK;
	}
	else replaceByTemplate(html, "{{status}}", "");
	server_sendHtml(client, (char*)html.c_str());
}

void server_file(socket_t * client, const char * fileName) {
	char * fileBuf;
	int fileLen = file_readAllBytes(fileName, &fileBuf);
	char header[10240];
	sprintf(header,
		"HTTP/1.1 200 OK\n"
		"Content-Length: %i\n"
		// "Content-Type: image/png\n"
		"Accept-Ranges: bytes\n"
		"Connection: close\n"
		"\n", fileLen);
	socket_write_string(client, header);
	printf(">> Sending file '%s' of size %i bytes...\n\n", fileName, fileLen);
	socket_write(client, fileBuf, fileLen);
	socket_close(client);
	free(fileBuf);
}

std::string server_addNewRecord(database_t db, char* query){
	char* queries[ARG_NUM];
	string names;
	string values;
	string tableName;
	for (int i = 0; i < ARG_NUM; i++){
		queries[i] = (char*)malloc(ARG_LENGTH*sizeof(char));
	}
	for (int i = 0; i < strlen(query); i++){
		if (query[i] == '+') query[i] = ' ';
	}
	char * pch = strtok(query, "&");
	int argCount = 0;
	while (pch != NULL){
		strcpy(queries[argCount++], pch);
		pch = strtok(NULL, "&");
		if (argCount > ARG_NUM) break;
	}
	for (int i = 0; i < argCount; i++){
		char argName[ARG_LENGTH / 2];
		char argVal[ARG_LENGTH];
		char* argValPointer = strstr(queries[i], "=");
		if (NULL == argValPointer) return NULL;
		strcpy(argName, queries[i]);
		argName[argValPointer - queries[i]] = '\0';
		strcpy(argVal, argValPointer + 1);
		if (i == argCount - 1){
			tableName.append(argVal);
			break;
		}
		names.append(argName);
		names += (i != argCount - 2)? ", ":"";
		values += "'";
		values.append(argVal);
		values += (i != argCount - 2) ? "', " : "'";
	}
	string sqlQuery;
	sqlQuery += "INSERT INTO " + tableName + "(" + names + ") VALUES(" + values + ");";
	db_executeSqlWithoutParam(db, sqlQuery.c_str());
	if (db->status == DB_OK)
		db->status = DB_INSERT_OK;
	for (int i = 0; i < ARG_NUM; i++){
		free(queries[i]);
	}
	return tableName;
}

std::string server_deleteRecord(database_t db, char* query){
	char* amper = strstr(query, "&");
	*amper = '\0';
	string param(query);
	string tableName(strstr(amper + 1, "=") + 1);
	string sqlQuery;
	sqlQuery += "DELETE FROM "+tableName+" WHERE "+param;
	db_executeSqlWithoutParam(db, sqlQuery.c_str());
	if (db->status == DB_OK)
		db->status = DB_DELETE_OK;
	return tableName;
}

std::string server_updateRecord(database_t db, char* query){
	char* queries[ARG_NUM];
	string values;
	string param;
	string tableName;
	for (int i = 0; i < ARG_NUM; i++){
		queries[i] = (char*)malloc(ARG_LENGTH*sizeof(char));
	}
	for (int i = 0; i < strlen(query); i++){
		if (query[i] == '+') query[i] = ' ';
	}
	char * pch = strtok(query, "&");
	int argCount = 0;
	while (pch != NULL){
		strcpy(queries[argCount++], pch);
		pch = strtok(NULL, "&");
		if (argCount > ARG_NUM) break;
	}
	for (int i = 0; i < argCount; i++){
		char argName[ARG_LENGTH / 2];
		char argVal[ARG_LENGTH];
		char* argValPointer = strstr(queries[i], "=");
		if (NULL == argValPointer) return NULL;
		strcpy(argName, queries[i]);
		argName[argValPointer - queries[i]] = '\0';
		strcpy(argVal, argValPointer + 1);
		if (i == 0){
			param.append(argName);
			param += " = '";
			param.append(argVal);
			param += "'";
			continue;
		}
		if (i == argCount - 1){
			tableName.append(argVal);
			break;
		}
		values.append(argName);
		values += " = '";
		values.append(argVal);
		values += (i != argCount - 2) ? "', " : "'";
	}
	values += " WHERE " + param + ";";
	values.insert(0, "UPDATE " + tableName + " SET ");
	db_executeSqlWithoutParam(db, values.c_str());
	if (db->status == DB_OK)
		db->status = DB_UPDATE_OK;
	for (int i = 0; i < ARG_NUM; i++){
		free(queries[i]);
	}
	return tableName;
}