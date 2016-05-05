#include "db.h"

struct database_s{
	sqlite3 * db;
	sqlite3_stmt * stmt;
	int status;
};

database_t db_new(void){
	return malloc(sizeof(struct database_s));
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

static void db_executeSqlWithoutParam(database_t self, const char* sqlQuery){
	//yep, not a wrapper, used because it makes other code much easier for this task.
	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return;
	}
	while (1) {
		int status  = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
}

int db_getCountOfScientists(database_t self){
	char* sqlQuery = "SELECT COUNT(*) FROM scientists";
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
			result = sqlite3_column_int(self->stmt, 0);
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
	return result;
}

char* db_getStatus(database_t self){
	static char status[50];
	switch (self->status){
	case 0:
		strcpy(status, "DB_OK");
		status[strlen("DB_OK")] = '\0';
		break;
	case 1:
		strcpy(status, "DB_ERROR");
		status[strlen("DB_ERROR")] = '\0';
		break;
	case 2:
		strcpy(status, "DB_INTERNAL_ERROR");
		status[strlen("DB_INTERNAL_ERROR")] = '\0';
		break;
	case 3:
		strcpy(status, "DB_CANT_OPEN");
		status[strlen("DB_CANT_OPEN")] = '\0';
		break;
	case 4:
		strcpy(status, "DB_TYPE_MISMATCH");
		status[strlen("DB_TYPE_MISMATCH")] = '\0';
		break;
	case 5:
		strcpy(status, "DB_RANGE");
		status[strlen("DB_RANGE")] = '\0';
		break;
	}
	return status;
}

scientist_t db_getScientistById(database_t self, int id){
	char sqlQuery[100] = "SELECT * FROM scientists WHERE ID = @id";
	scientist_t sc = NULL;
	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return NULL;
	}

	sqlite3_bind_int(self->stmt, 1, id);
	
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return NULL;
		}
		else if (SQLITE_ROW == status) {
			int count = sqlite3_column_count(self->stmt);
			sc = scientist_new(sqlite3_column_text(self->stmt, 1), 
				sqlite3_column_text(self->stmt, 2), 
				sqlite3_column_text(self->stmt, 3), 
				sqlite3_column_text(self->stmt, 4), 
				sqlite3_column_double(self->stmt, 5), 
				sqlite3_column_int(self->stmt, 6), 
				sqlite3_column_int(self->stmt, 7));
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
	return sc;
}

int db_getLastInsertedRowId(database_t self){
	int resIndex = -1;
	char* indexQuery = "SELECT last_insert_rowid()";
	int status = sqlite3_prepare_v2(self->db, indexQuery, strlen(indexQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return resIndex;
	}
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return -1;
		}
		else if (SQLITE_ROW == status){
			resIndex = sqlite3_column_int(self->stmt, 0);
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
	return resIndex;
}
int db_insertScientist(database_t self, scientist_t sc){
	char sqlQuery[500] = "INSERT INTO scientists(Surname, Name, Fathers, BirthDate, Quotation_index, Science_works, Books) VALUES(@Surname, @Name, @Fathers, @BirthDate, @Q_index, @Sc_works, @Books);";
	int resIndex = -1;

	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return -1;
	}

	sqlite3_bind_text(self->stmt, 1, sc->Surname, strlen(sc->Surname), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 2, sc->Name, strlen(sc->Name), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 3, sc->Fathers, strlen(sc->Fathers), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 4, sc->BirthDate, strlen(sc->BirthDate), SQLITE_TRANSIENT);
	sqlite3_bind_double(self->stmt, 5, sc->Quotation_index);
	sqlite3_bind_int(self->stmt, 6, sc->Science_works);
	sqlite3_bind_int(self->stmt, 7, sc->Books);

	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return -1;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}

	resIndex = db_getLastInsertedRowId(self);
	self->status = DB_OK;
	return resIndex;
}

void db_deleteScientistById(database_t self, int id){
	char sqlQuery[150] = "DELETE FROM scientists WHERE ID = @id";

	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return;
	}

	sqlite3_bind_int(self->stmt, 1, id);
	
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
}

void db_createScientistsTable(database_t self){
	FILE* queryFile = fopen("tableCreationScript.txt", "r");
	char initializingQuery[1000];
	fread(initializingQuery, sizeof(char), 1000, queryFile);
	db_executeSqlWithoutParam(self, initializingQuery);
	fclose(queryFile);
}

void db_updateScientistById(database_t self, scientist_t sc, int id){
	char sqlQuery[500] = "UPDATE scientists SET Surname = @Surname, Name = @Name, Fathers = @Fathers, BirthDate = @BirthDate, Quotation_index = @Q_index, Science_works = @Sc_works, Books = @Books WHERE ID = @id;";

	int status = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &self->stmt, NULL);
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return;
	}

	sqlite3_bind_text(self->stmt, 1, sc->Surname, strlen(sc->Surname), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 2, sc->Name, strlen(sc->Name), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 3, sc->Fathers, strlen(sc->Fathers), SQLITE_TRANSIENT);
	sqlite3_bind_text(self->stmt, 4, sc->BirthDate, strlen(sc->BirthDate), SQLITE_TRANSIENT);
	sqlite3_bind_double(self->stmt, 5, sc->Quotation_index);
	sqlite3_bind_int(self->stmt, 6, sc->Science_works);
	sqlite3_bind_int(self->stmt, 7, sc->Books);
	sqlite3_bind_int(self->stmt, 8, id);
	
	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			return;
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	self->status = DB_OK;
}

void db_getScientistsTask(database_t self, int K_ScWorks, int P_Books){
	char * sql = "SELECT ID FROM scientists WHERE Science_works > @ScWorks OR Books > @Books;";
	int status = sqlite3_prepare_v2(self->db, sql, strlen(sql), &self->stmt, NULL);
	int indexArr[100];
	int indexArrLen = 0;
	if (SQLITE_OK != status) {
		self->status = DB_ERROR;
		return;
	}

	int ScWorksIndex = sqlite3_bind_parameter_index(self->stmt , "@ScWorks");
	sqlite3_bind_int(self->stmt, ScWorksIndex, K_ScWorks);

	int BooksIndex = sqlite3_bind_parameter_index(self->stmt, "@Books");
	sqlite3_bind_int(self->stmt, BooksIndex, P_Books);

	while (1) {
		int status = sqlite3_step(self->stmt);
		if (SQLITE_ERROR == status) {
			self->status = DB_ERROR;
			
			return;
		}
		else if (SQLITE_ROW == status){
			indexArr[indexArrLen++] = sqlite3_column_int(self->stmt, 0);
			
		}
		else if (SQLITE_DONE == status) {
			break;
		}
	}
	for (int i = 0; i < indexArrLen; i++){
		scientist_t sc = db_getScientistById(self, indexArr[i]);
		scientist_print(sc);
		puts("");
		scientist_delete(sc);
	}
}