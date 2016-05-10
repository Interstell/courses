#pragma once
#include "headers.hpp"

#define MAX_HEADINGS_IN_TABLE 30

struct table_s{
	int recordsCount;
	int columnsCount;
	char* headings[MAX_HEADINGS_IN_TABLE];
	char name[50];
	char* headingsTypes[MAX_HEADINGS_IN_TABLE];
	std::string lastId;
};

using namespace std;

table_t table_new(database_t db, char* tableName);
void table_delete(table_t self);

int table_getColumnsCount(table_t self);

string table_getHtmlTableContent(table_t self, database_t db);
string table_getInputs(table_t self);


