#include "runtime.h"

#include <ctype.h>
#include <stdlib.h>

const char *g_computed{};
const char *g_last_choice{};

int rnum()
{
    return rand() + 1; // bias by one
}

// choose n of o
int choose(int n, int o)
{
    return (rnum() % o) < n ? 1 : 0;
}

int random_word(const char **wds)
{
        int i = 0, j = 0, k;
        const bool alliterate = g_last_choice != nullptr && (rand() % 4) != 0;

        /* See how many words there are that we can use. */
        for (k = 0; wds[k]; k++) {
                if (alliterate && (wds[k][0] == g_last_choice[0]))
                        j++;
        }
        i = k;
        if (j == 0) {
hoho:
                i = rnum() % i;
                g_last_choice = wds[i];
                g_computed = wds[i];
                return 1;
        } else {
                j = rnum() % j;
                for (k = 0; wds[k] != nullptr; k++)
                        if (wds[k][0] == tolower(g_last_choice[0])) {
                                if (wds[k] == g_last_choice)
                                        goto hoho;
                                if (j == 0) {
                                        g_last_choice = wds[k];
                                        g_computed = wds[k];
                                        return 1;
                                } else
                                        j--;
                        }
                goto hoho; // TODO: redo loop over j instead?
        }
}
