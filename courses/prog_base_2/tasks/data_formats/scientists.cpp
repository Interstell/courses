#include "scientists.h"
struct scientists_s{
	int numOfScientists;
	struct scientist_s* scientists[MAX_NUM_OF_SCIENTISTS_IN_FILE];
};

struct scientist_s{
	char firstName[20];
	char surname[20];
	char fathersName[30];
	char birthDate[20];
	char scienceDomain[30];
	int numOfAcademicDegrees;
	struct degree_s{
		char degreeName[50];
		char achievingDate[20];
		char thesisName[70];
	} degrees[MAX_NUM_OF_DEGREES];
	double quotationIndex;
	double HirschIndex;
	int scientificStudies;
	int patents;
};

scientists_t scientists_new(void){
	scientists_t arr = (scientists_t)malloc(sizeof(struct scientists_s));
	return arr;
}

void scientists_delete(scientists_t self){
	for (int i = 0; i < self->numOfScientists; i++){
		free(self->scientists[i]);
	}
	free(self);
}

int scientists_parseFromJsonFile(scientists_t self, char* fileName){
	FILE* fJSON = fopen(fileName, "r");
	if (NULL == fJSON) return 0;
	json_error_t error;
	json_t* root = json_loadf(fJSON, 0, &error);
	if (json_array_size(root) == 0) return 0;
	self->numOfScientists = json_array_size(root);
	for (int i = 0; i < self->numOfScientists; i++){
		self->scientists[i] = (struct scientist_s*)malloc(sizeof(struct scientist_s));
		json_t* sc = json_array_get(root, i);
		json_t* firstName = json_object_get(sc, "firstName");
		strcpy(self->scientists[i]->firstName, json_string_value(firstName));
		json_t* surname = json_object_get(sc, "surname");
		strcpy(self->scientists[i]->surname, json_string_value(surname));
		json_t* fathersName = json_object_get(sc, "fathersName");
		strcpy(self->scientists[i]->fathersName, json_string_value(fathersName));
		json_t* birthDate = json_object_get(sc, "birthDate");
		strcpy(self->scientists[i]->birthDate, json_string_value(birthDate));
		json_t* scienceDomain = json_object_get(sc, "scienceDomain");
		strcpy(self->scientists[i]->scienceDomain, json_string_value(scienceDomain));
		json_t* academicDegrees = json_object_get(sc, "academicDegrees");
		self->scientists[i]->numOfAcademicDegrees = json_array_size(academicDegrees);
		for (int j = 0; j < self->scientists[i]->numOfAcademicDegrees; j++){
			json_t* degree = json_array_get(academicDegrees, j);
			json_t* degreeName = json_object_get(degree, "degree");
			strcpy(self->scientists[i]->degrees[j].degreeName, json_string_value(degreeName));
			json_t* achievingDate = json_object_get(degree, "achievingDate");
			strcpy(self->scientists[i]->degrees[j].achievingDate, json_string_value(achievingDate));
			json_t* thesisName = json_object_get(degree, "thesisName");
			strcpy(self->scientists[i]->degrees[j].thesisName, json_string_value(thesisName));
		}
		json_t* quotationIndex = json_object_get(sc, "quotationIndex");
		self->scientists[i]->quotationIndex = json_real_value(quotationIndex);
		json_t* HirschIndex = json_object_get(sc, "HirschIndex");
		self->scientists[i]->HirschIndex = json_real_value(HirschIndex);
		json_t* scientificStudies = json_object_get(sc, "scientificStudies");
		self->scientists[i]->scientificStudies = json_integer_value(scientificStudies);
		json_t* patents = json_object_get(sc, "patents");
		self->scientists[i]->patents = json_integer_value(patents);
	}
	return 1;
}

int scientists_amount(scientists_t self){
	return self->numOfScientists;
}

void scientists_printByIndex(scientists_t self, int index){
	printf("----Scientist #%d----\n", index);
	printf("%s %s %s\n", self->scientists[index]->surname, self->scientists[index]->firstName, self->scientists[index]->fathersName);
	printf("Birth: %s\n", self->scientists[index]->birthDate);
	printf("Science domain: %s\n", self->scientists[index]->scienceDomain);
	printf("Degrees: \n");
	for (int i = 0; i < self->scientists[index]->numOfAcademicDegrees; i++){
		printf("\tDegree: %s\n", self->scientists[index]->degrees[i].degreeName);
		printf("\tAchieving date: %s\n", self->scientists[index]->degrees[i].achievingDate);
		printf("\tThesis name: %s\n", self->scientists[index]->degrees[i].thesisName);
		if (i != self->scientists[index]->numOfAcademicDegrees - 1) printf("\t---------\n");
	}
	printf("Quotation index: %.2f\n", self->scientists[index]->quotationIndex);
	printf("Hirsch index: %.2f\n", self->scientists[index]->HirschIndex);
	printf("Num of scientific studies: %d\n", self->scientists[index]->scientificStudies);
	printf("Num of patents: %d\n", self->scientists[index]->patents);
}