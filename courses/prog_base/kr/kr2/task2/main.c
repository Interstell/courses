#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct AUTO{
	int Year;
	char Model[100];
};
struct HUMAN{
	time_t BirthDate;
	struct AUTO * Car;
	char Name[100];
};
void fillRandAuto(struct AUTO *autos, int* numOfAutos){ //task #1 - fill by default
	char* names[] = { "Toyota", "Fiat", "Peugeot", "Mitsubishi", "Skoda", "Citroen", "Ferrari", "Lamborghini", "Pagani"};
	int size = sizeof(names) / sizeof(char*);
	strcpy(autos->Model, names[rand() % size]);
	autos->Year = rand() % 35 + 1980;
	*numOfAutos += 1;
}
void fillRandHuman(struct HUMAN * man, struct AUTO autos[], int numOfAutos, int* numOfPeople){ //task #1 - fill by default
	char* names[] = { "Max", "Jack", "Ivan", "Kolya", "Vasya", "Petya", "Igor", "Kinder", "Ruslan", "Dmitry", "Stas" };
	int size = sizeof(names) / sizeof(char*);
	strcpy(man->Name, names[rand() % size]);
	man->BirthDate = ((rand() % 10)+20) * 31536000 + (rand() % 12) * 2678400;
	man->Car = &(autos[*(numOfPeople)]);
	*numOfPeople += 1;
}
void fillHuman(struct HUMAN * man, struct AUTO autos[], char* Name, time_t date, int nOfCar, int* numOfPeople){
	strcpy(man->Name, Name);
	man->BirthDate = date;
	man->Car = &(autos[nOfCar]);
	*numOfPeople += 1;
}
void fillAuto(struct AUTO * car, char* model, int year, int* numOfCars){
	strcpy(car->Model, model);
	car->Year = year;
	*numOfCars += 1;
}
struct HUMAN* createHuman(int size){
	struct HUMAN* man = (struct HUMAN *)malloc(size);
	return man;
}
struct AUTO* createAuto(int size){
	struct AUTO* car = (struct HUMAN *)malloc(size);
	return car;
}
void deleteHuman(struct HUMAN* man){
	free(man);
}
void deleteAuto(struct AUTO* car){
	free(car);
}
void printHuman(struct HUMAN* man){
	printf("Name: %s\n", man->Name);
	struct tm* aTm = localtime(&(man->BirthDate));
	printf("   Birth date: %02d/%02d/%04d\n", aTm->tm_mday, aTm->tm_mon + 1, aTm->tm_year + 1900);
	printf("   Car: %s (%d)\n", man->Car->Model, man->Car->Year);
	puts("--------------------------");
}
void printCar(struct AUTO * car){
	printf("Model: %s\n", car->Model);
	printf("   Prod. year: %d\n", car->Year);
	puts("--------------------------");
}
void printAllPeople(struct HUMAN people[], int nOfPeople){
	for (int i = 0; i < nOfPeople; i++){
		printf("%d) ", i + 1);
		printHuman(&(people[i]));
	}
}
void printAllCars(struct AUTO cars[], int nOfCars){
	for (int i = 0; i < nOfCars; i++){
		printf("%d) ", i + 1);
		printCar(&(cars[i]));
	}
}
int humanCompare(struct HUMAN* man1, struct HUMAN* man2){
	if (!(strcmp(man1->Name, man2->Name) == 0)) return 0;
	else if (man1->BirthDate != man2->BirthDate) return 0;
	else if (man1->Car != man2->Car) return 0;
	return 1; // 1 = people are the same
}
int carCompare(struct AUTO* car1, struct AUTO* car2){
	if (!(strcmp(car1->Model, car2->Model) == 0)) return 0;
	else if (car1->Year != car2->Year) return 0;
	return 1; // 1 = cars are the same
}
int main(void){
	struct HUMAN people[20];
	struct AUTO autos[20];
	int numOfAutos = 0;
	int numOfPeople = 0;
	time_t t;
	srand((unsigned)time(NULL));
	fillRandAuto(&(autos[0]), &numOfAutos);
	fillRandHuman(&(people[0]), autos, numOfAutos, &numOfPeople);
	fillRandAuto(&(autos[1]), &numOfAutos);
	fillRandHuman(&(people[1]), autos, numOfAutos, &numOfPeople);
	fillRandAuto(&(autos[2]), &numOfAutos);
	fillRandHuman(&(people[2]), autos, numOfAutos, &numOfPeople);
	fillRandAuto(&(autos[3]), &numOfAutos);
	fillRandHuman(&(people[3]), autos, numOfAutos, &numOfPeople);
	puts("Hello!");
	puts("I have filled 4 people and 4 cars with random data. Here they are: ");
	puts("");
	printAllCars(autos, numOfAutos);
	printAllPeople(people, numOfPeople);
	
	puts("Other functions work well too, you can just look on their code :)");
	//fillHuman(&(people[1]), autos, "Max", 315532800, 0, &numOfPeople);
	puts("--------------------------");
	puts("Cars which are older than 5 years and whose owners are older than 20 years: ");
	time(&t);
	for (int i = 0; i < numOfAutos; i++){
		if ((2015 - autos[i].Year > 5) && (difftime(t, people[i].BirthDate)<631152000)){
			printf("* %s's %s (%d)\n", people[i].Name, autos[i].Model, autos[i].Year);
		}
	}
	getchar();
	return EXIT_SUCCESS;
}