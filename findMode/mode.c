#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int arr[], int s) {
	int i, j, min;

	for(i = 0; i < s - 1; i++) {
		min = i;

		for (j = i + 1; j < s; j++)
			if (arr[j] < arr[min])
				min = j;
		swap(&arr[i],&arr[min]);
	}
}

void printArr(int arr[], int s) {
	int i;
	for(i = 0; i < s; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int findMode(int arr[], int s) {
	int i, cur = arr[0], count = 1, maxVal, max = 0;
	for(i = 1; i < s; i++) {
		if (arr[i] == cur)
			count++;
		else if (count > max) {
			max = count;
			maxVal = cur;
			count = 1;
			cur = arr[i];
		} else {
			count = 1;
			cur = arr[i];
		}
	}

	if (count > max) {
		max = count;
		maxVal = cur;
		count = 1;
		cur = arr[i];
	} 
	return maxVal;
}

int main(void) {
	// int list[16] = {1,1,2,2,2,3,4,5,6,7,8,9,9,9,9,0};
	// int list[7] = {0, 1, 2, 3, 4, 4, 99};
	int list[5] = {1, 4, 9, 9, 4};
	// int list[4] = {9, 8, 7, 6, 10};
	// int list[1] = {5};

	int size = sizeof list / sizeof list[0];
	
	printf("List: ");	
	printArr(list, size);

	sort(list, size);

	printf("Mode: %d\n", findMode(list, size));
	return 0;
}
