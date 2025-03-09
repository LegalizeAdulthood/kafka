#pragma once

extern const char *g_computed;
extern const char *g_last_choice;

int rnum();
int choose(int n, int o);
int random_word(const char **wds);

#define CH(n_, o_) return choose((n_), (o_))
