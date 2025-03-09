/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher
 *      Permission is granted to do anything with this code except sell it
 *      or remove this message.
 */
#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

FILE *textp = nullptr;
FILE *specp = nullptr;
FILE *infile = nullptr;
std::string g_source_file;
std::string g_text_file{"kaf.text.cpp"};
std::string g_spec_file{"kaf.spec.cpp"};
int lineno{};

int init()
{
    /* These should be only defaults here... */

    if ((textp = fopen(g_text_file.c_str(), "w")) == nullptr)
    {
        perror(g_text_file.c_str());
        exit(1);
    }
    if ((specp = fopen(g_spec_file.c_str(), "w")) == nullptr)
    {
        perror(g_spec_file.c_str());
        exit(1);
    }
    if (g_source_file.empty())
    {
        infile = stdin;
    }
    else if ((infile = fopen(g_source_file.c_str(), "r")) == nullptr)
    {
        perror(g_source_file.c_str());
        exit(1);
    }
    fprintf(textp, "/* The user routine file. */\n\n");
    fprintf(specp, "/* The specification file. */\n\n");
    fprintf(specp, "#include \"kafgraf.h\"\n\n");
    return 0;
}
