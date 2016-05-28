#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include <jansson\jansson.h>
#include "scientist.hpp"
extern "C"{
#include "list.h"
}


typedef struct database_s* database_t;

#define DB_OK               0   
#define DB_ERROR			1   
#define DB_INTERNAL_ERROR   2   
#define DB_CANT_OPEN        3   
#define DB_TYPE_MISMATCH    4   
#define DB_RANGE            5  

database_t db_new(void);
void db_delete(database_t self);
void db_openDB(database_t self, const char* dbFileName);

list_t* db_getListOfScientistsFromDb(database_t db);


