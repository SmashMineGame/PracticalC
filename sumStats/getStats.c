# include <stdlib.h>
# include <stdio.h>
# include <math.h>

int prompt (char* p) {
	int output;
	printf("%s ",p);
	scanf("%d", &output);
	return output;
}

double* get_array(size_t l) {
	double* output = malloc(l*sizeof(double));
	for(size_t i = 0; i < l; i++) {
		printf("statList[%zu]: ", i);
		scanf("%lf", &output[i]);
	}
	return output;
}

double sum(double* arr, size_t l) {
	double output = 0;
	for(size_t i = 0; i < l; i++) {
		output += arr[i];
	}
	return output;
}

double mean(double* arr, size_t l) {
	double output = sum(arr, l);
	output /= l;
	return output;
}

double stdev(double* arr, size_t l) {
	double output = 0;
	double m = mean(arr, l);
	for (size_t i = 0; i < l; i++) {
		output += (arr[i] - m) * (arr[i] - m);
	}
	output = sqrt(output/l);
	return output;
}

int main() {
	int listLength = prompt("Length of List:");
	double* statList = get_array(listLength);
	
	double listSum = sum(statList, listLength);
	double listMean = mean(statList, listLength);
	double listStdev = stdev(statList, listLength);

	printf("sum:   %f\nmean:  %f\nstdev: %f\n", listSum, listMean, listStdev);

	return 0;
}
