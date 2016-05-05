#include "db.h"
#include "scientist.h"

int main(void) {
	database_t db = db_new();
	db_openDB(db, "scientists.db"); //db is already created, but empty
	
	db_createScientistsTable(db);
	scientist_t sc;
	sc = scientist_new("Legeza", "Petr", "Viktorovich", "1955-02-15", 3.5, 210, 8);
	int id1 = db_insertScientist(db, sc);
	scientist_print(sc);
	puts("");
	scientist_delete(sc);
	sc = scientist_new("Ivanov", "Ivan", "Ivanovich", "1946-12-04", 1.5, 12, 5);
	int id2 = db_insertScientist(db, sc);
	scientist_print(sc);
	puts("");
	scientist_delete(sc);
	puts("");
	sc = scientist_new("Rabinovich", "Igor", "Iosipovich", "1954-01-24", 2.4, 17, 6);
	int id3 = db_insertScientist(db, sc);
	scientist_print(sc);
	puts("");
	scientist_delete(sc);

	printf("Scientists in table: %d\n", db_getCountOfScientists(db));

	int minScWorks = 20;
	int minBooks = 5;
	printf("Scientists with Sc_works > %d OR Books > %d\n", minScWorks, minBooks);
	db_getScientistsTask(db, minScWorks, minBooks);

	db_deleteScientistById(db, id1); 
	db_deleteScientistById(db, id2);
	db_deleteScientistById(db, id3);


	db_delete(db);
	getchar();
	return 0;
}

