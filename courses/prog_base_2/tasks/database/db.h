#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "scientist.h"

#define DB_OK               0   

#define DB_ERROR			1   
#define DB_INTERNAL_ERROR   2   
#define DB_CANT_OPEN        3   
#define DB_TYPE_MISMATCH    4   
#define DB_RANGE            5   


typedef struct database_s* database_t;

database_t db_new(void);
void db_delete(database_t self);

void db_openDB(database_t self, const char* dbFileName);


/* Task */
int db_getCountOfScientists(database_t self);
void db_getScientistsTask(database_t self, int K_ScWorks, int P_Books);


/* CRUD */
scientist_t db_getScientistById(database_t self, int id);
int db_insertScientist(database_t self, scientist_t sc);
void db_deleteScientistById(database_t self, int id);
void db_createScientistsTable(database_t self);
void db_updateScientistById(database_t self, scientist_t sc, int id);

/* Other */
char* db_getStatus(database_t self);
int db_getLastInsertedRowId(database_t self);