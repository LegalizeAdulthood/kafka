/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher
 *      Permission is granted to do anything with this code except sell it
 *      or remove this message.
 */
#pragma once

enum
{
    STACKSIZE = 1024,
    HASHSIZE = 256
};

/* Stack elements for the generator machine. */

struct kkelt
{
    struct kknode *ke_node;
    struct kcarc *ke_arc;
};
