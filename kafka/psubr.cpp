/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher
 *      Permission is granted to do anything with this code except sell it
 *      or remove this message.
 *
 * Routines for the parser. These create and maintain the graph that the
 * parser is responsible for.
 */

#include "psubr.h"

#include "ast.h"
#include "stuff.h"

#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

knode *n;
knode *hashtab[256];
karc *avarc;
int i, c;

/* Enter a new rule. */

void newrule(char *name)
{
    knode *prev{};
    unsigned char hashind;

    hashind = phash(name);
    if (hashtab[hashind])
    {
        for (n = hashtab[hashind]; n != nullptr; n = n->kn_nnt)
        {
            if (!strcmp(n->kn_nodename, name))
            {
                while (n->kn_next)
                {
                    n = n->kn_next;
                }
                n->kn_next = (knode *) malloc(sizeof(knode));
                n = n->kn_next;
                goto gotit;
            }
            prev = n;
        }
        assert(prev != nullptr);
        if (n == nullptr)
        {
            n = prev->kn_nnt = (knode *) malloc(sizeof(knode));
        }
    }
    else
    {
        hashtab[hashind] = (knode *) malloc(sizeof(knode));
        n = hashtab[hashind];
    }
gotit:
    strcpy(n->kn_nodename, name);
    n->kn_nnt = n->kn_next = nullptr;
    n->kn_type = NodeType::NON_TERMINAL;
    n->kn_nodenumber = newnum2();
    avarc = n->kn_arc = nullptr; /* Set n->kn_arc to the arc when you
                                  * find one.
                                  */
                                 /* The new node is now in place. Now to collect the arcs... */
}

/* Enter a computed terminal. */

void docompterm()
{
    int fnum;

    n->kn_type = NodeType::COMPUTED;
    n->kn_next = n->kn_nnt = nullptr;
    n->kn_arc = nullptr;
    fnum = newnum();
    n->kn_fnum = fnum;
    /* Now we have to read in the actual function
     * definition. This is kept in "kaf.text.c", along
     * with the rest of the user-supplied C code.
     */
    if (transcribe(fnum))
    {
        fprintf(stderr, "Premature end of file.\n");
        exit(1);
    }
}

/* Enter a nonterminal in a rule. */

void dononterm(char *name)
{
    /* Found a non-terminal. Note that throughout
     * this process n will point to the main functor
     * and avarc will point the last used arc. Thus
     * when the end is found avarc->narc must be set = NULL.
     * (This will also occur immediately if the rule
     * is determined to be a computed terminal.)
     * Also references in arcs cannot be resolved
     * until all rules are in...
     */
    if (avarc)
    {
        avarc->ka_narc = (karc *) malloc(sizeof(karc));
        avarc = avarc->ka_narc;
    }
    else
    { /* This is the first one. */
        avarc = (karc *) malloc(sizeof(karc));
        n->kn_arc = avarc;
    }
    strcpy(avarc->ka_toname, name);
    avarc->ka_type = NodeType::NON_TERMINAL;
    avarc->ka_arcnumber = newnum2();
}

/* Enter a terminal. */

void doterm(char *name)
{
    /* Just set ka_toname to the name of the terminal and set ka_type
     * to be KTTERM.
     */

    if (avarc)
    {
        avarc->ka_narc = (karc *) malloc(sizeof(karc));
        avarc = avarc->ka_narc;
    }
    else
    { /* This is the first arc. */
        avarc = (karc *) malloc(sizeof(karc));
        n->kn_arc = avarc;
    }
    strcpy(avarc->ka_toname, name);
    avarc->ka_type = NodeType::TERMINAL;
    avarc->ka_arcnumber = newnum2();
}

/* Copy C code in defs section. */

void copyccode()
{
    int c;
    extern FILE *textp;

    for (;;)
    {
        while ((c = lex_input()) != '\n')
        {
            if (c == '\0')
            {
                fprintf(stderr, "Unexpected EOF.\n");
                exit(1);
            }
            putc(c, textp);
        }
        c = lex_input();
        if (c == '%')
        {
            /* { boo hiss */ if ((c = lex_input()) == '}')
            {
                return;
            }
            putc('\n', textp);
            putc('%', textp);
            putc(c, textp);
            continue;
        }
        putc('\n', textp);
        lex_unput(c);
    }
}
