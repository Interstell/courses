#include <math.h>

double calc(int n, int m){
	double x = 0,loop=0;
	double pi = 3.141592653589793238462643383279;
	int n0 = 7, n1 = 1, i, j;
	for (i = 1; i <= n; i++){
		loop = 0;
		for (j = 1; j <= m; j++){
			loop += pow(j, n1 + i);
		}
		x += sin(2 * pi / i)*sqrt(loop);
	}
	return x;
}