#include "headers.hpp"

static int table_columnsCount(database_t db, char* tableName){
	int res = 0;
	char sqlQuery[100];
	sprintf(sqlQuery, "pragma table_info(%s)", tableName); //no, pragmas do not work with sqlite3_bind
	int status = sqlite3_prepare_v2(db->db, sqlQuery, strlen(sqlQuery), &db->stmt, NULL);
	if (SQLITE_OK != status) {
		db->status = DB_ERROR;
		return -1;
	}
	while (1) {
		int status = sqlite3_step(db->stmt);
		if (SQLITE_ERROR == status) {
			db->status = DB_ERROR;
			return -1;
		}
		else if (SQLITE_ROW == status){
			res++;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	db->status = DB_OK;
	return res;
}

static void table_fillHeadings(table_t self, database_t db){
	char sqlQuery[100];
	sprintf(sqlQuery, "pragma table_info(%s)", self->name); //no, pragmas do not work with sqlite3_bind
	int status = sqlite3_prepare_v2(db->db, sqlQuery, strlen(sqlQuery), &db->stmt, NULL);
	if (SQLITE_OK != status) {
		db->status = DB_ERROR;
		return;
	}
	for (int i = 0; i < self->columnsCount; i++){
		self->headings[i] = (char*)malloc(100 * sizeof(char));
		self->headingsTypes[i] = (char*)malloc(100 * sizeof(char));
	}
	int currentHeading = 0;
	while (1) {
		int status = sqlite3_step(db->stmt);
		if (SQLITE_ERROR == status) {
			db->status = DB_ERROR;
			return;
		}
		else if (SQLITE_ROW == status){
			strcpy(self->headingsTypes[currentHeading], (const char*)sqlite3_column_text(db->stmt, 2));
			strcpy(self->headings[currentHeading++], (const char*)sqlite3_column_text(db->stmt, 1));
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	db->status = DB_OK;
}

static int table_recordsCount(table_t self, database_t db){
	int result = -1;
	char sqlQuery[100];
	sprintf(sqlQuery, "SELECT COUNT(*) FROM %s", self->name);
	int status = sqlite3_prepare_v2(db->db, sqlQuery, strlen(sqlQuery), &db->stmt, NULL);
	if (SQLITE_OK != status) {
		db->status = DB_ERROR;
		return -1;
	}	
	while (1) {
		int status = sqlite3_step(db->stmt);
		if (SQLITE_ERROR == status) {
			db->status = DB_ERROR;
			return -1;
		}
		else if (SQLITE_ROW == status){
			result = sqlite3_column_int(db->stmt, 0);
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	db->status = DB_OK;
	return result;
}

table_t table_new(database_t db, char* tableName){
	table_t table = new struct table_s;
	strcpy(table->name, tableName);
	table->columnsCount = table_columnsCount(db, tableName);
	table_fillHeadings(table, db);
	table->recordsCount = table_recordsCount(table, db);
	return table;
}

void table_delete(table_t self){
	for (int i = 0; i < self->columnsCount; i++){
		if (self->headings[i]) free(self->headings[i]);
		if (self->headingsTypes[i]) free(self->headings[i]);
	}
	delete self;
}

int table_getColumnsCount(table_t self){
	return self->columnsCount;
}

string table_getHtmlTableContent(table_t self, database_t db){
	string content;
	char sqlQuery[100];
	sprintf(sqlQuery, "SELECT * FROM %s", self->name);
	int status = sqlite3_prepare_v2(db->db, sqlQuery, strlen(sqlQuery), &db->stmt, NULL);
	if (SQLITE_OK != status) {
		db->status = DB_ERROR;
		return NULL;
	}

	while (1) {
		int status = sqlite3_step(db->stmt);
		if (SQLITE_ERROR == status) {
			db->status = DB_ERROR;
			return NULL;
		}
		else if (SQLITE_ROW == status){
			string row = "\t<tr>";
			string rowId;
			int count = sqlite3_column_count(db->stmt);
			string mainField((char*)sqlite3_column_text(db->stmt, 0));
			for (int i = 0; i < count; i++){
				string cell((char*)sqlite3_column_text(db->stmt, i));
				if (i == 0){
					rowId.append((char*)sqlite3_column_text(db->stmt, i));
					self->lastId.clear();
					self->lastId.append((char*)sqlite3_column_text(db->stmt, i));
				}
				string colName((char*)sqlite3_column_name(db->stmt, i));
				row += "<td id=\""+mainField+"_field#"+to_string(i)+"\">"+cell+"</td>";
			}
			string tableName(self->name);
			string mainName((char*)sqlite3_column_name(db->stmt, 0));
			row += "<td><a href=\"javascript:edit(" + rowId + "); \"><img class=\"edit_btn\" src=\"images/edit.png\"></a></td><td>"
				"<form action=\"/delete\" method=\"POST\">\n"
				"<button class=\"delete_form_btn\" type=\"submit\" name=\""+mainName+"\" value=\""+rowId+"\"><img class=\"delete_form_btn_img\" src=\"images/delete.png\"></button>"
				"<input type=\"hidden\" name=\"table_name\" value=\"" + tableName + "\">"
				"</form>"
				"</td></tr>";
			content += row + "\n";
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	db->status = DB_OK;
	return content;
}

string table_getInputs(table_t self){
	string inputs;
	for (int i = 0; i < self->columnsCount; i++){
		string heading(self->headings[i]);
		heading += " [<i>";
		heading.append(self->headingsTypes[i]);
		heading += "</i>]";
		string colName(self->headings[i]);
		inputs += "\t\t<span class=\"heading_input\">" + heading + "</span><br>\n";
		inputs += "\t\t<input id=\"input#"+to_string(i)+"\" type=\"text\" name=\"" + colName + "\" value=\"\"><br>\n";
	}
	return inputs;
}




