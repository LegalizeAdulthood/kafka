#pragma once

#include "node_type.h"

enum
{
    SSIZE = 100 /* Max size of terminals and nonterms.  */
};

struct karc;

struct knode
{
    NodeType kn_type;        /* See below. */
    char kn_nodename[SSIZE]; /* Terminal or non-term. */
    karc *kn_arc;            /* Pointer to list of arcs. */
    knode *kn_next;          /* Next rule for this non-term. */
    knode *kn_nnt;           /* Next non-term. */
    int kn_fnum;             /* The id number of the function. 0 if none. */
    int kn_nodenumber;       /* The (unique) id number of this node. */
};

struct karc
{
    karc *ka_narc;         /* Link. */
    knode *ka_to;          /* Thing pointed to. */
    char ka_toname[SSIZE]; /* Name of node pointed to. */
    NodeType ka_type;      /* Type of thing pointed to. */
    int ka_arcnumber;      /* The unique id of this arc. */
};
