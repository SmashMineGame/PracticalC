#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int checkSize(mpz_t n, int size)
{
	if (mpz_sizeinbase(n, 10) > size - 1)
	{
		return 0;
	}
	return 1;
}

int main()
{
	int number_of_digits = 1000;

	mpz_t prev, curr, temp;
	mpz_inits(prev, curr, temp, NULL);

	mpz_set_ui(prev, 1); // prev = 0;
	mpz_set_ui(curr, 0); // curr = 1;

	int count = 0;
	int stop = 1;

	while (stop)
	{
		stop = checkSize(curr, number_of_digits);

		mpz_set(temp, curr); // temp = curr;

		mpz_add(curr, curr, prev); // curr += prev;
		mpz_set(prev, temp);	   // prev = temp;

		count++;
	}

	gmp_printf("Fib num %d: %Zd\n", count, curr);

	mpz_clears(prev, curr, temp, NULL);
	return 0;
}