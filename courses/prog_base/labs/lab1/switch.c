#include <math.h>

int exec(int op, int a, int b) {
	int result;
	int data_size,temp;
	int n0 = 7, n1 = 1;
	double PI = 3.14159265358979323846;
	if (op < 0){
		temp = a;
		a = b;
		b = temp;
	}
	switch (op){
	case 0:
		result=-a;
		break;
	case 1:
		result=a + b;
		break;
	case 2:
		result=a - b;
		break;
	case 3:
		result=a * b;
		break;
	case 4:
		result = a / b;
		break;
	case 5:
		result = abs(a);
		break;
	case 6: 
		result = pow(a, b);
		break;
	case 7:
	case 13:
	case 77:
		result = a%b;
		break;
	case 8:
		result = max(a, b);
		break;
	case 9:
		result = min(a, b);
		break;
	case 10:
		switch (abs(b) % 8){
		case 0:
			data_size = sizeof(char);
			break;
		case 1:
			data_size = sizeof(signed char);
			break;
		case 2:
			data_size = sizeof(short);
			break;
		case 3:
			data_size = sizeof(unsigned int);
			break;
		case 4:
			data_size = sizeof(long);
			break;
		case 5:
			data_size = sizeof(unsigned long long);
			break;
		case 6:
			data_size = sizeof(float);
			break;
		case 7:
			data_size = sizeof(double);
			break;
		}
		result = abs(a)*data_size;
		break;
	case 11:
		if (a==0){
			result = 0;
		}
		else result = (n0 + 1)*PI*cos((n1 + 1)*a*b) / a;
		break;
	default:
		if (op < 100){
			result = (op % abs(a + 1)) + (op % abs(b + 1));
		}
		else if (op >= 100){
			result = -1;
		}
		break;
	}
	return result;
}