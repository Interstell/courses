#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n = 10, i, a[10]; //let's hope user enters 10 values
	for (i = 0; i < n; i++){
		scanf_s("%d", &a[i]);
	}
	for (i = 0; i < n; i++){
		if (a[i]>0){
			printf("%d ", a[i]);
		}
	}
	puts("");
	getchar();
	getchar();
}