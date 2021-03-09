#include <stdio.h>

void pass(char *name)
{
	printf("👍 The %s test case passed.", name);
}

void fail(char *name)
{
	printf("❌ The %s test case failed.", name);
}

int AUTF_assert(int check, char *name)
{
	if (check)
	{
		pass(name);
	}
	else
	{
		fail(name);
	}

	return check;
}

void pass_msg(char *msg)
{
	printf("👍 %s", msg);
}

void fail_msg(char *msg)
{
	printf("❌ %s", msg);
}

int AUTF_assert_msg(int check, char *msg)
{
	if (check)
	{
		pass_msg(msg);
	}
	else
	{
		fail_msg(msg);
	}
}