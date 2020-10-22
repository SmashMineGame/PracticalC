# include <stdio.h>
# include <stdlib.h>

int* insert(int* a, size_t l, int v, int p) {
	a = realloc(a, (l+1) * sizeof(int));

	for (int i = l-1; i > p; i--) {
		a[i+1] = a[i];
	}	
	a[p] = v;

	return a;
}

int main() {
	
	size_t size = 10;	
	int *nums = malloc(size * sizeof(int));

	for(size_t i = 0; i < size; i++) {
   		nums[i] = i;
		printf("%d, ", nums[i]);
	}
	printf("\n");

	int insertPosition = 2;

	nums = insert(nums, size, 100, insertPosition);

	for(size_t i = 0; i < size + 1; i++) {
		printf("%d, ", nums[i]);
	}
	printf("\n");

	return 0;
}
