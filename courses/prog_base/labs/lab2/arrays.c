#include <math.h>
#ifdef max
#undef max
#endif
void fillRand2(int arr[], int size){
	int i;
	time_t t;
	srand((unsigned) time(&t));
	for (i = 0; i < size; i++){
		arr[i] = rand() % 511-255;
	}
}
int checkRand2(int arr[], int size){
	int i;
	for (i = 0; i < size; i++){
		if ((arr[i]<-255) || (arr[i]>255)){
			return 0;
		}
	}
	return 1;
}
float meanValue(int arr[], int size){
	int i, sum = 0;
	for (i = 0; i < size; i++){
		sum += arr[i];
	}
	return sum / (float)size;
}
int maxValue(int arr[], int size){
	int i;
	int maxval = arr[0];
	for (i = 0; i < size; i++){
		if (arr[i]>maxval){
			maxval = arr[i];
		}
	}
	return maxval;
}
int meanIndex(int arr[], int size){
	int i, resIndex = 0;
	float meanval = meanValue(arr, size);
	double mindelta=256.0,delta;
	for (i = 0; i < size; i++){
		delta = abs(meanval - arr[i]);
		if (delta < mindelta){
			mindelta = delta;
			resIndex = i;
		}
	}
	return resIndex;
}
int maxIndex(int arr[], int size){
	int i;
	int maxval = arr[0];
	int maxInd = 0;
	for (i = 0; i < size; i++){
		if (arr[i]>maxval){
			maxval = arr[i];
			maxInd = i;
		}
	}
	return maxInd;
}
int maxOccurance(int arr[], int size){
	int i,j;
	int resValue=-1, occNum,maxoccNum=0;
	for (i = 0; i < size; i++){
		occNum = 0;
		for (j = 0; j < size; j++){
			if (arr[i] == arr[j]){
				occNum++;
			}
		}
		if (occNum > maxoccNum){
			resValue = arr[i];
			maxoccNum = occNum;
		}
		if ((occNum == maxoccNum)&&(arr[i]>resValue)){
			resValue = arr[i];
		}

	}
	return resValue;
}
int diff(int arr1[], int arr2[], int res[], int size){
	int i, result = 1;
	for (i = 0; i < size; i++){
		res[i] = arr1[i] - arr2[i];
		if (res[i]!=0) {
			result = 0;
		}
	}
	return result;
}
void divide(int arr1[], int arr2[], int res[], int size){ //unknown error occurs when naming "div"
	int i;
	for (i = 0; i < size; i++){
		res[i] = arr1[i] / arr2[i];
	}
}
int gt(int arr1[], int arr2[], int size){
	int i;
	for (i = 0; i < size; i++){
		if (arr1[i] <= arr2[i]){
			return 0;
		}
	}
	return 1;
}
void lor(int arr1[], int arr2[], int res[], int size){
	int i;
	for (i = 0; i < size; i++){
		res[i] = (arr1[i] || arr2[i]) ? 1 : 0;
	}
}