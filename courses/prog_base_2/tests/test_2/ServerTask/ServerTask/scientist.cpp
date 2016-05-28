#include "scientist.hpp"


scientist_t scientist_new(int Id, char* Surname, char* Name, char* BirthDate, double Quotation_index, int Books){
	if (NULL == Surname || NULL == Name) return NULL; //NOT NULL property in DB
	scientist_t sc = (scientist_t)malloc(sizeof(struct scientist_s));
	sc->Id = Id;
	strcpy(sc->Surname, Surname);
	strcpy(sc->Name, Name);
	strcpy(sc->BirthDate, BirthDate);
	sc->Quotation_index = Quotation_index;
	sc->Books = Books;
	return sc;
}

void scientist_delete(scientist_t self){
	free(self);
}

void scientist_delete_void(void* self){
	free((scientist_t)self);
}

json_t* scientist_serializeListToJson(list_t* list){
	json_t* res = json_array();
	for (int i = 0; i < list_getSize(list); i++){
		scientist_t sc = (scientist_t)list_get(list, i);
		json_t* scJSON = json_pack("{s:i, s:s, s:s, s:s, s:f, s:i}",
			"ID", sc->Id,
			"Surname", sc->Surname,
			"Name", sc->Name,
			"BirthDate", sc->BirthDate,
			"Quotation_index", sc->Quotation_index,
			"Science_works", sc->Books
			);
		json_array_append(res, scJSON);
	}
	return res;
}