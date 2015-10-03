#include <math.h>

int isExp2(int modmin){
	double b = (log(modmin) / log(2)) - (int)(log(modmin) / log(2));
	if (b==0){
		return 1;
	}
	else return 0;
}
int NumOfNeg(int a, int b, int c){
	int result = 0;
	if (a < 0) result++;
	if (b < 0) result++;
	if (c < 0) result++;
	return result;
}

int satisfies(int a, int b, int c) {
	int result=0;
	int n0 = 7, n1 = 1;
	int modmin, sum2;

	if (NumOfNeg(a,b,c)==3){
		modmin = abs(min(a, b, c));
		sum2 = a + b + c - min(a, b, c);
		if ((sum2 < -256) && (isExp2(modmin) == 1) && (modmin < 256)){
			return 1;
		}
		else if (((abs(sum2) - modmin) < 16) || (abs(sum2) < 16)){
			return 1;
		}

	}
	else if ((NumOfNeg(a,b,c)==1)||(NumOfNeg(a,b,c)==2)){ 
		if (NumOfNeg(a, b, c) == 1){
			if (min(a, b, c, )>-256){
				return 1;
			}
			else return 0;
		}
		if (NumOfNeg(a, b, c) == 2){
			if ((a + b + c - max(a, b, c))*(n0 + n1) > -256){
				return 1;
			}
			else return 0;
		}
	}
	else if (NumOfNeg(a,b,c)==0) {  
		if (max(a, b, c)*min(a, b, c) < 256){
			return 1;
		}
		else return 0;
	}
	return result;
}