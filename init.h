#pragma once

#include <stdio.h>
#include <string>

int init();
extern FILE *infile;
extern FILE *textp;
extern int lineno;
extern std::string g_source_file;
extern std::string g_text_file;
extern std::string g_spec_file;
