#include <stdio.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int[] arr, int s) {
	int i, j, min;

	for(i = 0; i < s - 1; i++) {
		min = i;

		for (j = i + 1; j < s; j++)
			if (arr[j] < arr[min])
				min = j;
		swap(&arr[i],&arr[min]);
	}
}

void printArr(int[] arr, int s) {
	int i;

	for(i = 0; i < s - 1; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(void) {
	int[] list = {1,2,3,4,5,6,7,8,9,0,0};
	int size = 11;
	printArr(list, size);
	return 0;
}
