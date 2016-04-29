#include "person.h"

struct person_s{
	char name[30];
	char surname[30];
	int birthYear;
	char key[100];
	char value[100];
};

person_t person_new(char* name, char* surname, int birthYear){
	person_t person = (person_t)malloc(sizeof(struct person_s));
	strcpy(person->name, name);
	strcpy(person->surname, surname);
	person->birthYear = birthYear;
	return person;
}

void person_free(person_t self){
	if (self) free(self);
}

char* person_getKey(person_t self){
	return self->surname;
}

char* person_getValue(person_t self){
	int count = sprintf(self->value, "%s %s, %d", self->surname, self->name, self->birthYear);
	self->value[count] = '\0';
	return self->value;
}

void person_insertToList(person_t self, HWND hWndList){
	SendMessage(hWndList, LB_INSERTSTRING, 0, (LPARAM)person_getKey(self));
	SendMessage(hWndList, LB_SETITEMDATA, 0, (LPARAM)person_getValue(self));
}