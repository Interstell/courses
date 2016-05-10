#include "headers.hpp"

using namespace std;

database_t db_new(void){
	return new struct database_s;
}


void db_delete(database_t self){
	sqlite3_finalize(self->stmt);
	sqlite3_close(self->db);
	delete self;
}


void db_openDB(database_t self, const char* dbFileName){
	int status = sqlite3_open(dbFileName, &self->db);
	if (SQLITE_OK != status) {
		self->status = DB_CANT_OPEN;
		return;
	}
	self->status = DB_OK;
}

void db_setTableCount(database_t self, int count){
	self->tableCount = count;
}

int db_getTableCount(database_t self){
	return self->tableCount;
}

int db_getListOfTables(database_t self, char* tableNames[]){
	char* sqlQuery = "SELECT name FROM sqlite_master WHERE type = \"table\"";
	int tableCount = 0;
	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	int result;
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return -1;
	}
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return -1;
		}
		else if (SQLITE_ROW == status){
			strcpy(tableNames[tableCount], (const char*)sqlite3_column_text(self->stmt, 0));
			if (strcmp(tableNames[tableCount], "sqlite_sequence") != 0) tableCount++;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
	return tableCount;
}

void db_fillTables(database_t self, char* dbTableNames[]){
	for (int i = 0; i < self->tableCount; i++){
		self->tables[i] = table_new(self, dbTableNames[i]);
	}
}

table_t db_getTableByName(database_t self, char* dbName){
	for (int i = 0; i < self->tableCount; i++){
		if (strcmp(self->tables[i]->name, dbName) == 0)
			return self->tables[i];
	}
	return NULL;
}

void db_executeSqlWithoutParam(database_t self, const char* sqlQuery){
	//yep, not a wrapper, used because it makes other code much easier for this task.
	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return;
	}
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return;
		}
		else if (SQLITE_CONSTRAINT == status){
			self->status = DB_NOT_UNIQUE;
			return;
		}
		else if (SQLITE_MISMATCH == status){
			self->status = DB_TYPE_MISMATCH;
			return;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
		else{
			self->status = DB_ERROR;
			return;
		}
	}
	self->status = DB_OK;
}


