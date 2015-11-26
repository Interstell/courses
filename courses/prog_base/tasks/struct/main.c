#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct CITY{
	char name[50];
	int population;
	double ltd; //latitude
	double lng; //longtitude
};
void count(int size, struct CITY cities[]){
	int count = 1;
	int* resindecies = (int*)malloc(size*sizeof(int));
	int arrIndex = 0;
	for (int i = 1; i < size; i++){
		double distance = 6371 * acos(sin(cities[0].ltd*0.0174533)*sin(cities[i].ltd*0.0174533) + cos(cities[0].ltd*0.0174533)*cos(cities[i].ltd*0.0174533)*cos(cities[0].lng*0.0174533 - cities[i].lng*0.0174533)); //distance on the sphere
		if (distance < 50){
			count++;
			resindecies[arrIndex] = i;
			arrIndex++;
		}
	}
	printf("NOTE! Assuming %s as (0;0)\n", cities[0].name);
	printf("Cities that are no farther than 50 km from the first city : %d\nThese cities are: %s, ", count, cities[0].name);
	for (int i = 0; i < arrIndex; i++){
		if (i == arrIndex - 1) printf("%s.", cities[resindecies[i]].name);
		else printf("%s, ", cities[resindecies[i]].name);
	}

	free(resindecies);
}
void print(int size, struct CITY* cities){
	for (int i = 0; i < size; i++){
		printf("%d. %s\n", i + 1, cities[i].name);
		printf("  Population: %d people\n", cities[i].population);
		printf("  Latitude: %.2lf%cN\n", cities[i].ltd, 248);
		printf("  Longtitude: %.2lf%cE\n", cities[i].lng, 248);
	}
}
void change(struct CITY *cities, const char* newValue){
	strcpy(cities->name, newValue);
}
int main(void){
	struct CITY cities[5] = { "Kyiv", 2799000, 50.43, 30.52, "Borispol", 60102, 50.35, 30.95, "Brovary", 100374, 50.5, 30.77, "Bucha", 42279, 50.37, 30.21, "Bila Tserkva", 206990, 49.78, 30.12 };
	int size = sizeof(cities) / (50+sizeof(int)+2*sizeof(double));
	char newName[50];
	int indexToChange = 1, result = 0;
	print(size, cities);
	count(size, cities);
	puts("");
	do {
		fflush(stdin);
		printf("Type the number of the city and it's new name(e.g. \"3 Lviv\"):\n");
		result = scanf("%d %s", &indexToChange, newName);
		if (result < 2 || indexToChange <= 0 || indexToChange > size) puts("Wrong input. Try again.");
	} while (result < 2 || indexToChange <= 0 || indexToChange > size);
	change(&(cities[indexToChange-1]), newName);
	print(size, cities);
	getchar();
	getchar();
	return EXIT_SUCCESS;
}