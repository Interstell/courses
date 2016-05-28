#include "database.hpp"

struct database_s{
	sqlite3 * db;
	sqlite3_stmt * stmt;
	int status;
};

database_t db_new(void){
	return (database_t)malloc(sizeof(struct database_s));
}

void db_delete(database_t self){
	sqlite3_finalize(self->stmt);
	sqlite3_close(self->db);
	free(self);
}

void db_openDB(database_t self, const char* dbFileName){
	int status = sqlite3_open(dbFileName, &self->db);
	if (SQLITE_OK != status) {
		self->status = DB_CANT_OPEN;
		return;
	}
	self->status = DB_OK;
}

list_t* db_getListOfScientistsFromDb(database_t self){
	char sqlQuery[100] = "SELECT * FROM scientists";
	list_t* scList = list_new_dealloc(scientist_delete_void);

	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return NULL;
	}

	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return NULL;
		}
		else if (SQLITE_ROW == status) {
			scientist_t sc = scientist_new(
				sqlite3_column_int(self->stmt, 1),
				(char*)sqlite3_column_text(self->stmt, 2),
				(char*)sqlite3_column_text(self->stmt, 3),
				(char*)sqlite3_column_text(self->stmt, 4),
				sqlite3_column_double(self->stmt, 5),
				sqlite3_column_int(self->stmt, 6)
				);
			list_push_back(scList, sc);
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
	return scList;
}