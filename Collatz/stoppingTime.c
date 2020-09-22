#include <stdlib.h>
#include <stdio.h>

int collatz(int n) {
	int count = 0;

	while (n != 1) {
		if (n % 2 == 0) {n /= 2;}
		else {n = 3*n + 1;}
		count++;
	}

	return count;
}

int findMaxCollatz(int max) {
	int running = 0;
	int i;
	for (i = 1; i <= max; i++) {
		int cur = collatz(i);
		if (cur > running) {
			running = i;
		}
	}
	return running;
}

int main(){
	int maximumVal = 100000;
	
	int maximumFound = findMaxCollatz(maximumVal);	
	printf("%d has a stopping time of %d", maximumFound, collatz(maximumFound));

	return 0;
}
