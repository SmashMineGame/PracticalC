# include <stdio.h>
# include <stdlib.h>

int* resize (int *a, size_t l, size_t nl) {
	int* na = malloc(nl * sizeof(int));
	
	int s = l < nl ? l : nl;

	for (int i = 0; i < s; i++) {
		na[i] = a[i];
	}
	free(a);

	return na;
}

int main() {
	int *nums = malloc(10 * sizeof(int));

	for(size_t i = 0; i < 10; i++) {
   		nums[i] = i;
		printf("%d, ", nums[i]);
	}
	printf("\n");

	nums = resize(nums, 10, 20);
	
	for(size_t i = 0; i < 20; i++) {
		printf("%d, ", nums[i]);
	}
	printf("\n");

	return 0;
}
