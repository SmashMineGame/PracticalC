#include <stdio.h>
#include <stdlib.h>
#include "hashbrown.h"

int main(int argc, char *argv[])
{
    hashbrown *hb = hb_make(100);
    printf("made a new hashbrown! length: %zu\n", hb_len(hb));

    hb_set(hb, "Bob", 10);
    hb_set(hb, "Jane", 35);

    hb_dump(hb);

    int val = 0;
    hb_get(hb, "Bob", &val);
    printf("Bob -> %d\n", val);

    if (!hb_get(hb, "Joe", &val))
    {
        printf("Joe's not in the table.\n");
    }
    else
    {
        printf("Joe -> %d\n", val);
    }

    hb_remove(hb, "Bob");

    hb_free(hb);

    return 0;
}