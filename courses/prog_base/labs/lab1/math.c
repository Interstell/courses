#include <math.h>

double calc(double x, double y, double z) {
	double a;
	double a0, a1, a2;
	double n0 = 7, n1 = 1;
	a0 = pow(x, y + 1) / pow(x - y, 1 / z);
	a1 = y / ((n0 + 1)*abs(x + y));
	a2 = sqrt(abs(cos(y) / sin(x) + n1));
	a = a0 + a1 + a2;
	if ((isfinite(a))&&(z!=0)){
		return a;
	}
	else {
		return nan("") ;
	}
}
	
