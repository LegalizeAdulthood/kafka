
/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher
 *      Permission is granted to do anything with this code except sell it
 *      or remove this message.
 *
 * Some useful things.
 */

#include <stdio.h>
#include <stdlib.h>

#include <config/getpid.h>

#include "maketext.h"
#include "output.h"

enum
{
    DEFAULT = 3
};

int nflag = 0;

int main(int ac, char **av)
{
    /* The main function for babble. */

    int i, j;
    extern int lpos;

    srand(getpid());

    if (ac > 1)
    {
        j = atoi(av[1]);
        if (j < 0)
        {
            j = -j;
            nflag = 1;
        }
        if (j == 0)
        {
            for (i = 0; i < 100; i++)
            {
                maketext("start");
                kkoutput("@");
                lpos = 0;
                putchar('\n');
                putchar('\n');
            }
            exit(0);
        }
        for (i = 0; i < j; i++)
        {
            maketext("start");
            kkoutput("@");
        }
        putchar('\n');
        exit(0);
    }
    i = DEFAULT;
    while (i--)
    {
        srand(rand());
        maketext("start");
        kkoutput("@");
    }
    putchar('\n');
    exit(0);
}
