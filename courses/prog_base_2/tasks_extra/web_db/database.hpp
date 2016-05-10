#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "headers.hpp"

#define DB_OK               0   
#define DB_ERROR			1   
#define DB_INTERNAL_ERROR   2   
#define DB_CANT_OPEN        3   
#define DB_TYPE_MISMATCH    4   
#define DB_RANGE            5  
#define DB_INSERT_OK		6
#define DB_UPDATE_OK		7
#define DB_DELETE_OK		8
#define DB_NOT_UNIQUE		9

#define MAX_TABLES_IN_DB 20

struct database_s{
	sqlite3 * db;
	sqlite3_stmt * stmt;
	int status;
	int tableCount;
	table_t tables[MAX_TABLES_IN_DB];
};

database_t db_new(void);
void db_delete(database_t self);
void db_setTableCount(database_t self, int count);
int db_getTableCount(database_t self);

void db_openDB(database_t self, const char* dbFileName);

int db_getListOfTables(database_t self, char* tableNames[]);
void db_fillTables(database_t self, char* dbTableNames[]);
table_t db_getTableByName(database_t self, char* dbName);
void db_executeSqlWithoutParam(database_t self, const char* sqlQuery);


