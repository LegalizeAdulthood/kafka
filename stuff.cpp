/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher
 *      Permission is granted to do anything with this code except sell it
 *      or remove this message.
 *
 * Assorted things.
 */
#include "stuff.h"

#include "psubr.h"

#include <stdio.h>

extern FILE *specp, *textp;

/* The hashing function. Note that hashtables have to be of size 256.
 * They probably don't need to be very big, and the fn is simple...
 */

unsigned char phash(char *string)
{
    unsigned char rv = 0;
    while (*string)
        rv += *(string++);
    return (rv);
}

/* This function reads a C function from the input file. It is kept in
 * the file pointed to by outp. It takes the function number as an argument
 * (the function will not have arguments). Note that this will be messed
 * up by unbalanced brackets in comments.
 */

int transcribe(int num)
{
    /* Note that we must add the first bracket... */

    extern FILE *textp;
    char c;
    int brct;

    fprintf(textp, "\nint _kkFunc%d()\n{\n", num);
    brct = 1;
    while (c = lex_input())
    { /* This is the lex input function. */
        if (c == '{')
            brct++;
        if (c == '}')
            brct--;
        putc(c, textp);
        if (!brct)
            return (0);
    }
    /* Reached EOF. */
    return (1);
}

/* "Gensym" for user supplied C code names. */

int newnum()
{
    static int n = 0;

    n++;
    return (n);
}

/* "Gensym" for arcnumbers and nodenumbers. */

int newnum2()
{
    static int n = 0;

    n++;
    return (n);
}
