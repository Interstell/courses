#include "sqlite3.h"
#include <stdio.h>
int sample(void){

	const char * dbFile = "test.db";
	sqlite3 * db = NULL;
	int rc = 0;

	rc = sqlite3_open(dbFile, &db);
	if (SQLITE_OK != rc) {
		printf("Can't open\n");
		return 1;
	}

	int minHeight = 150;
	int minWeight = 80;
	const char * sql = "SELECT * FROM Human WHERE Height > @height AND Weight < @weight;";

	sqlite3_stmt * stmt = NULL;

	rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
	if (SQLITE_OK != rc) {
		printf("Can't prepare statement\n");
		return 1;
	}

	int heightArgIndex = sqlite3_bind_parameter_index(stmt, "@height");
	sqlite3_bind_int(stmt, heightArgIndex, minHeight);

	int weightArgIndex = sqlite3_bind_parameter_index(stmt, "@weight");
	sqlite3_bind_int(stmt, weightArgIndex, minWeight);

	while (1) {
		rc = sqlite3_step(stmt);
		if (SQLITE_ERROR == rc) {
			printf("step error\n");
			return 1;
		}
		else if (SQLITE_DONE == rc) {
			break;
		}
		else if (SQLITE_ROW == rc){
			int count = sqlite3_column_count(stmt);
			for (int i = 0; i < count; i++) {
				const char * colName = sqlite3_column_name(stmt, i);
				const char * colType = sqlite3_column_decltype(stmt, i);
				const char * value = sqlite3_column_text(stmt, i);
				printf("%10s [%7s] = %s\n", colName, colType, value);
			}
			printf("\n");
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	getchar();
	return 0;
}