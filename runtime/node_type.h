#pragma once

enum class NodeType
{
    TERMINAL = 1,     /* kn_arc and kn_next will be NULL. */
    NON_TERMINAL = 2, /* Non-terminal. */
    COMPUTED = 3      /* Computed terminal. kn_arc->ka_func will
                       * be used to decide what the value of the
                       * terminal will be.
                       */
};
