#include "scientists.h"

int main(void){
	scientists_t sc = scientists_new();
	int isOK = scientists_parseFromJsonFile(sc, "scientists.json");
	if (!isOK) exit(EXIT_FAILURE);

	for (int i = 0; i < scientists_amount(sc); i++){
		scientists_printByIndex(sc, i);
		puts("");
	}

	scientists_delete(sc);
	getchar();
	return EXIT_SUCCESS;
}