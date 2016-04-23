#include "scientist.h"


scientist_t scientist_new(char* Surname, char* Name, char* Fathers, char* BirthDate, double Quotation_index, int Science_works, int Books){
	if (NULL == Surname || NULL == Name) return NULL; //NOT NULL property in DB
	scientist_t sc = malloc(sizeof(struct scientist_s));
	strcpy(sc->Surname, Surname);
	strcpy(sc->Name, Name);
	strcpy(sc->Fathers, Fathers);
	strcpy(sc->BirthDate, BirthDate);
	sc->Quotation_index = Quotation_index;
	sc->Science_works = Science_works;
	sc->Books = Books;
	return sc;
}

void scientist_delete(scientist_t self){
	free(self);
}

void scientist_print(scientist_t self){
	if (NULL == self){
		printf("NULL\n");
		return;
	}
	printf("%10s : %s\n", "Surname", self->Surname);
	printf("%10s : %s\n", "Name", self->Name);
	printf("%10s : %s\n", "Fathers", self->Fathers);
	printf("%10s : %s\n", "BirthDate", self->BirthDate);
	printf("%10s : %.2f\n", "Q_index", self->Quotation_index);
	printf("%10s : %d\n", "Sc_works", self->Science_works);
	printf("%10s : %d\n", "Books", self->Books);
}

