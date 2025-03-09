#pragma once

enum
{
    KTTERM = 1,  /* kn_arc and kn_next will be NULL. */
    KTNTERM = 2, /* Non-terminal. */
    KTCOMP = 3   /* Computed terminal. kn_arc->ka_func will
                  * be used to decide what the value of the
                  * terminal will be.
                  */
};
