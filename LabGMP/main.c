#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int checkSize(mpz_t n, int size)
{
	// printf("%d", mpz_sizeinbase(n, 10));
	if (mpz_sizeinbase(n, 10) > size)
	{
		char **temp = malloc(sizeof(char) * (size + 1));

		printf("%d\n", gmp_asprintf(temp, "%Zd", n));

		if (gmp_asprintf(temp, "%Zd", n) == size)
		{
			free(temp);
			return 0;
		}
		free(temp);
	}
	return 1;
}

int main()
{
	printf("start\n");
	mpz_t prev, curr;
	mpz_init(prev);
	mpz_init(curr);

	mpz_set_ui(prev, 0); // e = 0;
	mpz_add(curr, a, b); // c = a + b;

	int count = 0;

	// gmp_printf("[a: %Zd]\n", a);

	while (checkSize(curr, 1000))
	{
		mpz_t tb, temp;
		mpz_init(tb);
		mpz_init(temp);

		mpz_set(tb, b);		 // tb = b;
		mpz_set(temp, curr); // tc = c;

		mpz_add(curr, curr, b); // c += b;
		mpz_set(b, temp);		// b = tc;
		mpz_set(a, tb);			// a = tb;

		mpz_clear(tb);
		mpz_clear(temp);

		count++;
	}

	gmp_printf("Fib num %d: %Zd\n", count, curr);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	return 0;
}
