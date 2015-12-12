#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>
void sortPatients(struct PATIENT pts[], int n);
void sortDoctors(struct DOCTOR docs[], int n);
void JumpTo(int x, int y);
void printBottle(int x, int y);
struct DOCTOR{
	int dId;
	int Experience;
	int nOfPatients;
	int Patients[20];
	char Surname[30];
	char Name[20];
	char Specialization[30];
};
struct PATIENT{
	int pId;
	int BirthYear;
	int Doctors[20];
	int nOfDoctors;
	char Surname[30];
	char Name[20];
	char Sex[10];
	char Address[50];
	char Diagnoses[50];
	char Status[50];
};

enum COLORS {NORMAL = 240, SELECTED = 252, HEADER = 249};
void printVerticalLine(int x, int y1, int y2, char symbol, int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = y1; i < y2; i++){
		JumpTo(x, i);
		printf("%c", symbol);
	}
}
void deleteDoctor(struct DOCTOR doctors[], int numOfDandP[], int n){
	doctors[n].Surname[0] = 123;
	sortDoctors(doctors, numOfDandP[0]);
	numOfDandP[0] -= 1;
}
int deletePatient(struct PATIENT patients[], int numOfDandP[], int n){
	patients[n].Surname[0] = 123;
	sortPatients(patients, numOfDandP[1]);
	numOfDandP[1] -= 1;
}
int getDoctorIndexById(struct DOCTOR doctors[], int num, int dId){
	for (int i = 0; i < num; i++){
		if (doctors[i].dId == dId) return i;
	}
	return -1;
}
int getPatientIndexById(struct PATIENT patients[], int num, int pId){
	for (int i = 0; i < num; i++){
		if (patients[i].pId == pId) return i;
	}
	return -1;
}
void DoctorConstructor(struct DOCTOR *doctor, char* Surname, char* Name, char* Specialization, int Experience, int Patients[], int numOfPatients, int dId){
	strcpy(doctor->Surname, Surname);
	strcpy(doctor->Name, Name);
	strcpy(doctor->Specialization, Specialization);
	doctor->Experience = Experience;
	for (int i = 0; i < numOfPatients; i++){
		doctor->Patients[i] = Patients[i];
	}
	doctor->nOfPatients = numOfPatients;
	doctor->dId = dId;
}
void PatientConstructor(struct PATIENT *patient, char* Surname, char* Name, char* Sex, char* Address, char* Diagnoses, int BirthYear, int Doctors[], int numOfDoctors, char* Status, int pId){
	strcpy(patient->Surname, Surname);
	strcpy(patient->Name, Name);
	strcpy(patient->Sex, Sex);
	strcpy(patient->Address, Address);
	strcpy(patient->Diagnoses, Diagnoses);
	patient->BirthYear = BirthYear;
	strcpy(patient->Status, Status);
	patient->nOfDoctors = numOfDoctors;
	for (int i = 0; i < numOfDoctors; i++){
		patient->Doctors[i] = Doctors[i];
	}
	patient->pId = pId;
}
void ChangeSize(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	BOOL ok;
	coord.X = 120;
	coord.Y = 50;
	ok = SetConsoleScreenBufferSize(hStdout, coord);
	SMALL_RECT test = { 0, 0, coord.X - 1, coord.Y - 1 };
	SetConsoleWindowInfo(hStdout, ok, &test);
}
void PrintMenu(char* list[], int selected, int x, int y, int size){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	for (int i = 0; i < size; i++){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == selected) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SELECTED);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NORMAL);
		printf("%s", list[i]);
		coord.Y++;
	}
}
void JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}
void printRect(int x1, int y1, int x2, int y2, char border, int color){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x1;
	pos.Y = y1;
	SetConsoleTextAttribute(hConsole, color);
	for (pos.X; pos.X <= x2; pos.X++){
		for (pos.Y; pos.Y <= y2; pos.Y++){
			JumpTo(pos.X, pos.Y);
			if ((pos.X == x1) || (pos.X == x2) || (pos.Y == y1) || (pos.Y == y2)){
				printf("%c", border);
			}
			else printf(" ");
		}
		pos.Y = y1;
	}
}
int RunMainMenu(void){
	char*commands[] = { "View Patients", "View Doctors", "Create new Patient", "Create new Doctor", "Link Patient to Doc", "Link Doc to Patient", "Statistics", "Exit" };
	int size = sizeof(commands) / sizeof(int*);
	static int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(commands, selected, 5, 5, size);
	while (1){
		int button = _getch();
		if (button == 13 || button == 'd') return selected;
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMenu(commands, selected, 5, 5, size);
	}
}
void sortDoctors(struct DOCTOR docs[], int n){
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (docs[i].Surname[0]>docs[i + 1].Surname[0]){
				struct DOCTOR temp = docs[i];
				docs[i] = docs[i + 1];
				docs[i + 1] = temp;
			}
		}
	}
}
void sortPatients(struct PATIENT pts[], int n){
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (pts[i].Surname[0]>pts[i + 1].Surname[0]){
				struct PATIENT temp = pts[i];
				pts[i] = pts[i + 1];
				pts[i + 1] = temp;
			}
		}
	}
}
int runPatientsMenu(struct PATIENT patients[], int sortedPatients[], int nOfPatients, int x1, int y1, int x2, int y2){
	char** pts = (char**)malloc(nOfPatients*sizeof(char));
	for (int i = 0; i < nOfPatients; i++){
		pts[i] = (char*)malloc(100 * sizeof(char));
	}
	for (int i = 0; i < nOfPatients; i++){
		sprintf(pts[i], "%d) %s %c. (%d)", i+1, patients[i].Surname, patients[i].Name[0], patients[i].BirthYear);
	}
	int size = nOfPatients;

	printRect(x1, y1, x2, y2 + nOfPatients, ' ', NORMAL);	
	static int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(pts, selected, x1, y1, size);
	printVerticalLine(x1 - 2, y1, y1 + nOfPatients, '|', 250);
	while (1){
		int button = _getch();
		if (button == 13 || button == 'd'){
			for (int i = 0; i < nOfPatients; i++){
				free(pts[i]);
			}
			return selected;
		}
		else if (button == 'a'){
			printRect(x1, y1, x2, y2 + nOfPatients, ' ', NORMAL);
			printVerticalLine(x1 - 2, y1, y1 + nOfPatients + 4, ' ', 250);
			return -1;
		}
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMenu(pts, selected, x1, y1, size);
	}
	
}
void readData(struct DOCTOR doctors[], int sizeD, struct PATIENT patients[], int sizeP, int numOfDandP[]){
	FILE *DB, *PB, *SYS;
	DB = fopen("b_doctors.txt", "rb");
	PB = fopen("b_patients.txt", "rb");
	SYS = fopen("b_system.txt", "rb");
	fread(doctors, sizeD, 1, DB);
	fread(patients, sizeP, 1, PB);
	fread(numOfDandP, sizeof(int), 2, SYS);
	fflush(DB);
	fflush(PB);
	fflush(SYS);
	fclose(SYS);
	fclose(DB);
	fclose(PB);
}
void writeData(struct DOCTOR doctors[], int sizeD, struct PATIENT patients[], int sizeP, int numOfDandP[]){
	FILE *DB, *PB, *SYS;
	DB = fopen("b_doctors.txt", "wb");
	PB = fopen("b_patients.txt", "wb");
	SYS = fopen("b_system.txt", "wb");
	fwrite(doctors, sizeD, 1, DB);
	fwrite(patients, sizeP, 1, PB);
	fwrite(numOfDandP, sizeof(int), 2, SYS);
	fflush(DB);
	fflush(PB);
	fflush(SYS);
	fclose(SYS);
	fclose(DB);
	fclose(PB);
}
int viewPatientInfo(struct PATIENT patients[], struct DOCTOR doctors[], int n, int nOfDoctors){
	char* list[40];
	for (int i = 0; i < 40; i++){
		list[i] = (char*)malloc(100 * sizeof(char));
	}
	sprintf(list[0], "Name: %s", patients[n].Name);
	sprintf(list[1], "Surname: %s", patients[n].Surname);
	sprintf(list[2], "Sex: %s", (patients[n].Sex[0] == 'M' || patients[n].Sex[0] == 'm') ? "Male" : "Female");
	sprintf(list[3], "Year of Birth: %d", patients[n].BirthYear);
	sprintf(list[4], "Address: %s", patients[n].Address);
	sprintf(list[5], "Diagnoses: %s", patients[n].Diagnoses);
	sprintf(list[6], "Status: %s", patients[n].Status);
	for (int i = 7; i < 7 + patients[n].nOfDoctors; i++){
		if (getDoctorIndexById(doctors, nOfDoctors, patients[n].Doctors[i - 7]) == -1){
			sprintf(list[i], "Doctor #%d : <FIRED>", i - 6);
		}
		else sprintf(list[i], "Doctor #%d : %s %c. (%s)", i - 6, doctors[getDoctorIndexById(doctors, nOfDoctors, patients[n].Doctors[i - 7])].Surname, doctors[getDoctorIndexById(doctors, nOfDoctors, patients[n].Doctors[i - 7])].Name[0], doctors[getDoctorIndexById(doctors, nOfDoctors, patients[n].Doctors[i - 7])].Specialization);
		//sprintf(list[i], "Doctor #%d : %s %c. (%s)", i - 6, doctors[patients[n].Doctors[i - 7]].Surname, doctors[patients[n].Doctors[i - 7]].Name[0], doctors[patients[n].Doctors[i - 7]].Specialization);
	}
	sprintf(list[7 + patients[n].nOfDoctors], "%s", "Note! Doctors can be linked in \"P&D Linking\" menu");
	sprintf(list[7 + patients[n].nOfDoctors + 1], "%s", "DELETE this patient.");
	int size = 7 + patients[n].nOfDoctors + 2;
	printRect(50, 5, 100, 5 + size, ' ', NORMAL);
	int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(list, selected, 50, 5, size);
	printVerticalLine(48, 5, 5 + size, '|', 250);
	while (1){
		int button = _getch();
		if (button == 13 || button == 'd'){
			return selected;
		}
		else if (button == 'a'){
			printRect(50, 5, 100, 5 + size, ' ', NORMAL);
			for (int i = 0; i < 40; i++){
				free(list[i]);
			}
			printVerticalLine(48, 5, 5 + size + 4, ' ', 250);
			return -1;
		}
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMenu(list, selected, 50, 5, size);
	}
	
}
void setColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
int createNewPatient(struct PATIENT patients[], int numOfDandP[]){
	int n = numOfDandP[1];
	printRect(25, 5, 80, 17, 177, SELECTED);
	JumpTo(35, 6);
	setColor(HEADER);
	printf("%s", "Fill new patient's card with data.");
	JumpTo(27, 8);
	printf("Name: ");
	setColor(NORMAL);
	fgets(patients[n].Name, 20, stdin);
	patients[n].Name[strlen(patients[n].Name) - 1] = '\0';
	if (strcmp(patients[n].Name, "x") == 0){
		printRect(25, 5, 80, 17, ' ', SELECTED);
		return 0;
	}
	JumpTo(27, 9);
	setColor(HEADER);
	printf("Surname: ");
	setColor(NORMAL);
	fgets(patients[n].Surname, 30, stdin);
	patients[n].Surname[strlen(patients[n].Surname) - 1] = '\0';
	JumpTo(27, 10);
	setColor(HEADER);
	printf("Sex (Male/Female): ");
	setColor(NORMAL);
	scanf("%s", patients[n].Sex);
	fflush(stdin);
	JumpTo(27, 11);
	setColor(HEADER);
	printf("Year of birth: ");
	setColor(NORMAL);
	scanf("%d", &(patients[n].BirthYear));
	fflush(stdin);
	JumpTo(27, 12);
	setColor(HEADER);
	printf("Address: ");
	setColor(NORMAL);
	fgets(patients[n].Address, 30, stdin);
	patients[n].Address[strlen(patients[n].Address) - 1] = '\0';
	JumpTo(27, 13);
	setColor(HEADER);
	printf("Diagnoses: ");
	setColor(NORMAL);
	fgets(patients[n].Diagnoses, 30, stdin);
	patients[n].Diagnoses[strlen(patients[n].Diagnoses) - 1] = '\0';
	patients[n].nOfDoctors = 0;
	patients[n].pId = rand() % 1000000 + 100;
	strcpy(patients[n].Status, "Sick");
	numOfDandP[1] += 1;
	JumpTo(27, 15);
	printf("Press any key to continue...");
	_getch();
	printRect(25, 5, 80, 17, ' ', SELECTED);
}
void changePatientInfo(struct PATIENT patients[], int n, int param){
	if (param>=0 && param<=6) printRect(30, 20, 70, 24, 177, SELECTED);
	JumpTo(32, 22);
	setColor(HEADER);
	switch (param){
	case 0:
		printf("Name: ");
		break;
	case 1:
		printf("Surname: ");
		break;
	case 2:
		printf("Sex (Male/Female): ");
		break;
	case 3:
		printf("Year of birth: ");
		break;
	case 4:
		printf("Address: ");
		break;
	case 5:
		printf("Diagnoses: ");
		break;
	case 6:
		printf("Status :");
		break;
	}
	setColor(NORMAL);
	switch (param){
	case 0:
		fgets(patients[n].Name, 20, stdin);
		patients[n].Name[strlen(patients[n].Name) - 1] = '\0';
		break;
	case 1:
		fgets(patients[n].Surname, 30, stdin);
		patients[n].Surname[strlen(patients[n].Surname) - 1] = '\0';
		break;
	case 2:
		scanf("%s", patients[n].Sex);
		fflush(stdin);
		break;
	case 3:
		scanf("%d", &(patients[n].BirthYear));
		fflush(stdin);
		break;
	case 4:
		fgets(patients[n].Address, 30, stdin);
		patients[n].Address[strlen(patients[n].Address) - 1] = '\0';
		break;
	case 5:
		fgets(patients[n].Diagnoses, 30, stdin);
		patients[n].Diagnoses[strlen(patients[n].Diagnoses) - 1] = '\0';
		break;
	case 6:
		fgets(patients[n].Status, 30, stdin);
		patients[n].Status[strlen(patients[n].Status) - 1] = '\0';
		break;
	}
	if (param >= 0 && param <= 6) printRect(30, 20, 70, 24, ' ', SELECTED);
}
int runDoctorsMenu(struct DOCTOR doctors[], int sortedDoctors[], int nOfDoctors, int x1, int y1, int x2, int y2){
	char** dcs = (char**)malloc(nOfDoctors*sizeof(char));
	for (int i = 0; i < nOfDoctors; i++){
		dcs[i] = (char*)malloc(100 * sizeof(char));
	}
	for (int i = 0; i < nOfDoctors; i++){
		sprintf(dcs[i], "%d) %s %c. (%s)", i + 1, doctors[i].Surname, doctors[i].Name[0], doctors[i].Specialization);
	}
	int size = nOfDoctors;
	printRect(x1, y1, x2, y2 + nOfDoctors, ' ', NORMAL);
	static int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(dcs, selected, x1, y1, size);
	printVerticalLine(x1 - 2, y1, y1 + nOfDoctors, '|', 250);
	while (1){
		int button = _getch();
		if (button == 13 || button == 'd'){
			for (int i = 0; i < nOfDoctors; i++){
				free(dcs[i]);
			}
			return selected;
		}
		else if (button == 'a'){
			printRect(x1, y1, x2, y2 + nOfDoctors, ' ', NORMAL);
			printVerticalLine(x1 - 2, y1, y1 + nOfDoctors + 4, ' ', 250);
			return -1;
		}
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMenu(dcs, selected, x1, y1, size);
	}
}
int viewDoctorInfo(struct DOCTOR doctors[], struct PATIENT patients[], int n, int nOfPatients){
	char* list[40];
	for (int i = 0; i < 40; i++){
		list[i] = (char*)malloc(100 * sizeof(char));
	}
	sprintf(list[0], "Name: %s", doctors[n].Name);
	sprintf(list[1], "Surname: %s", doctors[n].Surname);
	sprintf(list[2], "Specialization: %s", doctors[n].Specialization);
	sprintf(list[3], "Experience: %d years", doctors[n].Experience);
	for (int i = 4; i < 4 + doctors[n].nOfPatients; i++){
		if (getPatientIndexById(patients, nOfPatients, doctors[n].Patients[i - 4]) == -1){
			sprintf(list[i], "Patient #%d : <TEMPERED>", i - 3);
		}
		else sprintf(list[i], "Patient #%d : %s %c. (%s)", i - 3, patients[getPatientIndexById(patients, nOfPatients, doctors[n].Patients[i - 4])].Surname, patients[getPatientIndexById(patients, nOfPatients, doctors[n].Patients[i - 4])].Name[0], patients[getPatientIndexById(patients, nOfPatients, doctors[n].Patients[i - 4])].Diagnoses);
		//sprintf(list[i], "Patient #%d : %s %c. (%s)", i - 3, patients[doctors[n].Patients[i - 4]].Surname, patients[doctors[n].Patients[i - 4]].Name[0], patients[doctors[n].Patients[i - 4]].Diagnoses);
	}
	sprintf(list[4 + doctors[n].nOfPatients], "%s", "Note! Patients can be linked in \"P&D Linking\" menu");
	sprintf(list[4 + doctors[n].nOfPatients + 1], "%s", "DELETE this doctor.");
	int size = 4 + doctors[n].nOfPatients + 2;
	printRect(60, 5, 120, 5 + size, ' ', NORMAL);
	int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(list, selected, 60, 5, size);
	printVerticalLine(58, 5, 5 + size, '|', 250);
	while (1){
		int button = _getch();
		if (button == 13 || button == 'd'){
			return selected;
		}
		else if (button == 'a'){
			printRect(60, 5, 120, 5 + size, ' ', NORMAL);
			for (int i = 0; i < 10; i++){
				free(list[i]);
			}
			printVerticalLine(58, 5, 5 + size + 4, ' ', 250);
			return -1;
		}
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMenu(list, selected, 60, 5, size);
	}
}
void changeDoctorInfo(struct DOCTOR doctors[], int n, int param){
	if (param >= 0 && param <= 3) printRect(30, 20, 70, 24, 177, SELECTED);
	JumpTo(32, 22);
	setColor(HEADER);
	switch (param){
	case 0:
		printf("Name: ");
		break;
	case 1:
		printf("Surname: ");
		break;
	case 2:
		printf("Specialization: ");
		break;
	case 3:
		printf("Experience: ");
		break;
	}
	setColor(NORMAL);
	switch (param){
	case 0:
		fgets(doctors[n].Name, 20, stdin);
		doctors[n].Name[strlen(doctors[n].Name) - 1] = '\0';
		break;
	case 1:
		fgets(doctors[n].Surname, 30, stdin);
		doctors[n].Surname[strlen(doctors[n].Surname) - 1] = '\0';
		break;
	case 2:
		fgets(doctors[n].Specialization, 30, stdin);
		doctors[n].Specialization[strlen(doctors[n].Specialization) - 1] = '\0';
		break;
	case 3:
		scanf("%d", &(doctors[n].Experience));
		fflush(stdin);
		break;
	}
	if (param >= 0 && param <= 3) printRect(30, 20, 70, 24, ' ', SELECTED);
}
int createNewDoctor(struct DOCTOR doctors[], int numOfDandP[]){
	int n = numOfDandP[0];
	printRect(25, 5, 80, 17, 177, SELECTED);
	JumpTo(35, 6);
	setColor(HEADER);
	printf("%s", "Fill new doctor's card with data.");
	JumpTo(27, 8);
	printf("Name: ");
	setColor(NORMAL);
	fgets(doctors[n].Name, 20, stdin);
	doctors[n].Name[strlen(doctors[n].Name) - 1] = '\0';
	if (strcmp(doctors[n].Name, "x") == 0){
		printRect(25, 5, 80, 17, ' ', SELECTED);
		return 0;
	}
	JumpTo(27, 9);
	setColor(HEADER);
	printf("Surname: ");
	setColor(NORMAL);
	fgets(doctors[n].Surname, 30, stdin);
	doctors[n].Surname[strlen(doctors[n].Surname) - 1] = '\0';
	JumpTo(27, 10);
	setColor(HEADER);
	printf("Specialization: ");
	setColor(NORMAL);
	fgets(doctors[n].Specialization, 30, stdin);
	doctors[n].Specialization[strlen(doctors[n].Specialization) - 1] = '\0';
	JumpTo(27, 11);
	setColor(HEADER);
	printf("Experience (years):  ");
	setColor(NORMAL);
	scanf("%d", &(doctors[n].Experience));
	fflush(stdin);
	JumpTo(27, 13);
	printf("Press any key to continue...");
	doctors[n].nOfPatients = 0;
	doctors[n].dId = rand() % 1000000 + 100;
	numOfDandP[0] += 1;
	_getch();
	printRect(25, 5, 80, 17, ' ', SELECTED);
}
void printStat(struct DOCTOR doctors[], struct PATIENT patients[], int numOfDandP[]){
	printRect(30, 5, 80, 40, 177, SELECTED);
	int start = 7;
	JumpTo(32, start);
	setColor(HEADER);
	puts("Patients without doctors:");
	setColor(NORMAL);
	for (int i = 0; i < numOfDandP[1]; i++){
		if (patients[i].nOfDoctors == 0){
			JumpTo(32, ++start);
			printf("%d) %s %c. (%d)", start - 7, patients[i].Surname, patients[i].Name[0], patients[i].BirthYear);
		}
	}
	if (start == 7){
		JumpTo(32, ++start);
		printf("None.");
	}
	setColor(HEADER);
	JumpTo(32, ++start);
	puts("Doctors without patients:");
	setColor(NORMAL);
	int count = 1;
	for (int i = 0; i < numOfDandP[0]; i++){
		if (doctors[i].nOfPatients == 0){
			JumpTo(32, ++start);
			printf("%d) %s %c. (%s)", count++, doctors[i].Surname, doctors[i].Name[0], doctors[i].Specialization);
		}
	}
	if (count == 1){
		JumpTo(32, ++start);
		printf("None.");
	}
	setColor(HEADER);
	JumpTo(32, ++start);
	puts("All specializations of doctors:");
	setColor(NORMAL);
	count = 1;
	for (int i = 0; i < numOfDandP[0]; i++){
		int flag = 0;
		for (int j = i+1; j < numOfDandP[0]; j++){
			if (strcmp(doctors[j].Specialization, doctors[i].Specialization) == 0) flag = 1;
		}
		if (flag == 0){
			JumpTo(32, ++start);
			printf("%d) %s", count++, doctors[i].Specialization);
		}
	}
	int maxExpInd = 0;
	for (int i = 1; i < numOfDandP[0]; i++){
		if (doctors[i].Experience > doctors[maxExpInd].Experience) maxExpInd = i;
	}
	setColor(HEADER);
	JumpTo(32, ++start);
	puts("The most experienced doctor:");
	setColor(NORMAL);
	JumpTo(32, ++start);
	printf("%s %c. (%s) : %d years", doctors[maxExpInd].Surname, doctors[maxExpInd].Name[0], doctors[maxExpInd].Specialization, doctors[maxExpInd].Experience);
	int maxAgeInd = 0;
	for (int i = 1; i < numOfDandP[1]; i++){
		if (patients[i].BirthYear < patients[maxAgeInd].BirthYear) maxAgeInd = i;
	}
	setColor(HEADER);
	JumpTo(32, ++start);
	puts("The oldest patient: ");
	setColor(NORMAL);
	JumpTo(32, ++start);
	printf("%s %c. (%d)", patients[maxAgeInd].Surname, patients[maxAgeInd].Name[0], patients[maxAgeInd].BirthYear);
	int minAgeInd = 0;
	for (int i = 1; i < numOfDandP[1]; i++){
		if (patients[i].BirthYear > patients[maxAgeInd].BirthYear) minAgeInd = i;
	}
	setColor(HEADER);
	JumpTo(32, ++start);
	puts("The youngest patient: ");
	setColor(NORMAL);
	JumpTo(32, ++start);
	printf("%s %c. (%d)", patients[minAgeInd].Surname, patients[minAgeInd].Name[0], patients[minAgeInd].BirthYear);
	
	while (!_kbhit()){
		printBottle(23, 20);
		printBottle(81, 20);
		Sleep(1000);
		printRect(23, 20, 23 + 6, 20 + 12, 32, NORMAL);
		printRect(85, 20, 81 + 6, 20 + 12, 32, NORMAL);
	}
	printRect(30, 5, 100, 45, 32, SELECTED);
}
void printBottle(int x, int y){
	int strongColors[] = { 32, 64, 96, 16, 48 };
	int weakColors[] = { 160, 192, 224, 144, 176 };
	int randC = rand() % (sizeof(weakColors)/sizeof(int));
	int weakG = 112;
	int strongG = 128;
	int brown = 96;
	int weak = weakColors[randC];
	int strong = strongColors[randC];
	printVerticalLine(x, y + 7, y + 8, 32, weakG);
	printVerticalLine(x, y + 8, y + 12, 32, weak);
	printVerticalLine(x + 1, y + 1, y + 3, 32, weakG);
	printVerticalLine(x + 1, y + 6, y + 7, 32, weakG);
	printVerticalLine(x + 1, y + 7, y + 8, 32, strongG);
	printVerticalLine(x + 1, y + 8, y + 12, 32, strong);
	printVerticalLine(x + 1, y + 12, y + 13, 32, weak);
	printVerticalLine(x + 2, y, y + 2, 32, brown);
	printVerticalLine(x + 2, y + 2, y + 3, 32, strongG);
	printVerticalLine(x + 2, y + 3, y + 6, 32, weakG);
	printVerticalLine(x + 2, y + 6, y + 7, 32, strongG);
	printVerticalLine(x + 2, y + 7, y + 8, 32, weakG);
	printVerticalLine(x + 2, y + 8, y + 11, 32, weak);
	printVerticalLine(x + 2, y + 11, y + 12, 32, strong);
	printVerticalLine(x + 2, y + 12, y + 13, 32, weak);
	printVerticalLine(x + 3, y, y + 2, 32, brown);
	printVerticalLine(x + 3, y + 2, y + 8, 32, strongG);
	printVerticalLine(x + 3, y + 8, y + 11, 32, strong);
	printVerticalLine(x + 3, y + 11, y + 13, 32, weak);
	printVerticalLine(x + 4, y, y + 2, 32, brown);
	printVerticalLine(x + 4, y + 2, y + 3, 32, strongG);
	printVerticalLine(x + 4, y + 3, y + 6, 32, weakG);
	printVerticalLine(x + 4, y + 6, y + 8, 32, strongG);
	printVerticalLine(x + 4, y + 8, y + 12, 32, strong);
	printVerticalLine(x + 4, y + 12, y + 13, 32, weak);
	printVerticalLine(x + 5, y + 1, y + 3, 32, weakG);
	printVerticalLine(x + 5, y + 6, y + 7, 32, weakG);
	printVerticalLine(x + 5, y + 7, y + 8, 32, strongG);
	printVerticalLine(x + 5, y + 8, y + 12, 32, strong);
	printVerticalLine(x + 5, y + 12, y + 13, 32, weak);
	printVerticalLine(x + 6, y + 7, y + 8, 32, weakG);
	printVerticalLine(x + 6, y + 8, y + 12, 32, weak);
}


int main(void){
	struct DOCTOR doctors[20];
	struct DOCTOR temp[20];
	struct PATIENT patients[20];
	int numOfDandP[2] = { 3, 2 };
	int pts[2] = { 1, 2 };
	int dcs[2] = { 1, 2 };
	int dPointer = 0, pPointer = 0;
	int doctorsSorted[20], patientsSorted[20];
	FILE *DB, *PB, *SYS;
	srand((unsigned)time(NULL));
	//DoctorConstructor(&(doctors[0]), "Yashan", "Olga", "Surger", 5, pts, sizeof(pts)/sizeof(int), 1);
	//DoctorConstructor(&(doctors[1]), "Levoshko", "Kate", "Physyologist", 10, pts, sizeof(pts) / sizeof(int), 2);
	//DoctorConstructor(&(doctors[2]), "Pakhomova", "Eugenya", "Surger", 3, pts, sizeof(pts) / sizeof(int), 3);
	//PatientConstructor(&(patients[0]), "Krysyuk", "Andrey", "M", "Kyiv", "Clever", 1998, dcs, sizeof(dcs) / sizeof(int), "DEAD", 1);
	//PatientConstructor(&(patients[1]), "Davydov", "Gleb", "M", "Kyiv", "Crazy", 1997, dcs, sizeof(dcs) / sizeof(int), "HEALTHY", 2);
	readData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
	sortDoctors(doctors, numOfDandP[0]);
	sortPatients(patients, numOfDandP[1]);
	writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
	ChangeSize();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	system("cls");
	int patient = 0, toChange, doctor = 0, toChange2;
	while (1){
		int res = RunMainMenu();
		switch (res){
		case 0:
			while (1){
				patient = runPatientsMenu(patients, patientsSorted, numOfDandP[1], 27, 5, 70, 5);
				if (patient == -1) break;
				else {
					while (1){
						toChange = viewPatientInfo(patients, doctors, patient, numOfDandP[0]);
						if (toChange == -1) break;
						else if (toChange == 7 + patients[patient].nOfDoctors + 1){
							printRect(48, 5, 100, 5 + 7 + patients[patient].nOfDoctors + 2, ' ', NORMAL);
							deletePatient(patients, numOfDandP, patient);
							writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
							break;
						}
						else{
							changePatientInfo(patients, patient, toChange);
						}
						writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
					}
				}
				
			}
			break;
		case 1:
			while (1){
				doctor = runDoctorsMenu(doctors, doctorsSorted, numOfDandP[0], 27, 5, 70, 5);
				if (doctor == -1) break;
				else {
					while (1){
						toChange2 = viewDoctorInfo(doctors, patients, doctor, numOfDandP[1]);
						if (toChange2 == -1) break;
						else if (toChange2 == 4 + doctors[doctor].nOfPatients + 1){
							printRect(58, 5, 120, 5 + 4 + doctors[doctor].nOfPatients + 2, ' ', NORMAL);
							deleteDoctor(doctors, numOfDandP, doctor);
							writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
							break;
						}
						else{
							changeDoctorInfo(doctors, doctor, toChange2);
						}
						writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
					}
				}
			}
			break;
		case 2:
			createNewPatient(patients, numOfDandP);
			sortPatients(patients, numOfDandP[1]);
			writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
			break;
		case 3:
			createNewDoctor(doctors, numOfDandP);
			sortDoctors(doctors, numOfDandP[0]);
			writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
			break;
		case 4:
			while (1){
				int doc = runDoctorsMenu(doctors, doctorsSorted, numOfDandP[0], 27, 5, 70, 5);
				if (doc == -1) break;
				int pts = runPatientsMenu(patients, patientsSorted, numOfDandP[1], 63, 5, 100, 5);
				if (pts == -1) continue;
				else {
					patients[pts].Doctors[patients[pts].nOfDoctors] = doctors[doc].dId;
					patients[pts].nOfDoctors += 1;
					doctors[doc].Patients[doctors[doc].nOfPatients] = patients[pts].pId;
					doctors[doc].nOfPatients += 1;
					printRect(27, 5, 120, 15, ' ', NORMAL);
					break;
				}
			}
			writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
			break;
		case 5:
			while (1){
				int pts = runPatientsMenu(patients, patientsSorted, numOfDandP[1], 27, 5, 70, 5);
				if (pts == -1) break;
				int doc = runDoctorsMenu(doctors, doctorsSorted, numOfDandP[0], 63, 5, 100, 5);
				if (doc == -1) continue;
				else {
					patients[pts].Doctors[patients[pts].nOfDoctors] = doctors[doc].dId;
					patients[pts].nOfDoctors += 1;
					doctors[doc].Patients[doctors[doc].nOfPatients] = patients[pts].pId;
					doctors[doc].nOfPatients += 1;
					printRect(27, 5, 120, 15, ' ', NORMAL);
					break;
				}
			}
			break;
		case 6:
			printStat(doctors, patients, numOfDandP);
			break;
		case 7:
			writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
			exit(EXIT_SUCCESS);
			break;
		}
			
	}
	writeData(doctors, sizeof(doctors), patients, sizeof(patients), numOfDandP);
}