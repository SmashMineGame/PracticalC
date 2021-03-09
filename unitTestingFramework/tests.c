#include "AUTF.h";

int maximum(int a, int b)
{
	return a > b ? a : b;
}

void test_maximum()
{
	int first_greater = maximum(10, 5) == 10;
	int last_greater = maximum(4, 15) == 15;
	int neither_greater = maximum(12, 12) == 12;

	AUTF_assert(first_greater, "First_Greater");
	AUTF_assert(last_greater, "Last_Greater");
	AUTF_assert(neither_greater, "Neither_Greater");
}

int main()
{
	return 0;
}