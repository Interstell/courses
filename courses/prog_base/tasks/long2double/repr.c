#include <math.h>

double long2double(long long num){
	int i, charNum, exp, expSum = 0,signflag;
	double fraction = 0, result = 0;
	char binary[64] = "";
	long long numCopy;
	const float FLOAT_NEGATIVE_INFINITY = ((float)(-1e308 * 10)); //found in Google
	if (num == 0) return 0;
	signflag = (num > 0) ? 1 : -1;
	for (charNum = 63; charNum >= 0; charNum--){
		numCopy = num;
		numCopy = numCopy >> 1;
		numCopy = numCopy << 1;
		binary[charNum] = (num == numCopy) ? '0' : '1';
		num = num >> 1;
	}
	for (charNum = 12, exp = -1; charNum <= 63; charNum++, exp--){
		if (binary[charNum] == '1'){
			fraction = fraction + pow(2, exp);
		}
	}
	for (charNum = 11, exp = 0; charNum >= 1; charNum--, exp++){
		if (binary[charNum] == '1'){
			expSum = expSum + pow(2, exp);
		}
	}
	if ((expSum == 0) && (fraction == 0) && (binary[0] =='0')){  //+0
		result = +0;
	}
	else if ((expSum == 0) && (fraction == 0) && (binary[0] == '1')){  //-0
		result=-0.0;
	}
	else if ((expSum == 2047) && (fraction == 0) && (binary[0] == '0')){ //+inf
		result = INFINITY;
	}
	else if ((expSum == 2047) && (fraction == 0) && (binary[0] == '1')){ //-inf
		return FLOAT_NEGATIVE_INFINITY;
	}
	else if ((expSum == 2047) && (fraction != 0) && (binary[0] == '0')){ //+NaN
		return nan("");
	}
	else if ((expSum == 2047) && (fraction != 0) && (binary[0] == '1')){ //-NaN
		return -nan("");  //may not work correctly, depending on the system \_(-_-)_/; taken from StackOveflow after long googling. 
	}
	else if ((expSum == 0) && (fraction != 1)){      //denormalized
		result = signflag*fraction*pow(2, -1022);
	}
	else {
		result = signflag*(1+fraction)*pow(2, expSum - 1023); //normalized
	}
	
	return result;
}