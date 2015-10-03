#include <stdio.h>
#include <stdlib.h>

int main(void){
	int h = 4;
	int min = 11;
	int code = 62;

	int time = (h*60)+min;
	double ResPrice;
	if ((code >= 10) && (code <= 999)){
		switch (code){
		case 44:
			ResPrice = time * 0.77;
			break;
		case 62:
			ResPrice = time * 0.8;
			break;
		case 32:
			ResPrice = time * 0.95;
			break;
		case 692:
		case 697:
			ResPrice = time * 1.5;
			break;
		default:
			ResPrice = time * 1;
			break;
		}
		printf("%.2f hrn", ResPrice);
	}
	else printf("Error");
	getchar();
}