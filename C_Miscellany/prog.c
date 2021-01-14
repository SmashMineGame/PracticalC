#include <stdio.h>
#include <stdlib.h>

/*
./prog
./prog > hello.txt
./prog | grep -n "pipe"
./prog 2> errors.txt
./prog 1> output.txt
./prog &> all.txt
rm all.txt hello.txt only-errors.txt only-output.txt
*/

int main()
{
    fprintf(stdout, "%s", "stdout gets piped!\n");

    // Must manually end program -- printing to stderr doesn't.
    fprintf(stderr, "%s", "stderr doesn't get piped\n");

    fprintf(stdout, "%s", "stdout gets piped again!\n");

    return 0;
}
