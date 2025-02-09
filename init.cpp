/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher 
 *	Permission is granted to do anything with this code except sell it
 *	or remove this message.
 */
#include "init.h"

#include <stdio.h>
#include <stdlib.h>

FILE *textp = NULL;
FILE *specp = NULL;
FILE *infile = NULL;
extern char *sourcefile;
int lineno{};

int init()
{
	/* These should be only defaults here... */

	if ((textp = fopen("kaf.text.cpp", "w")) == NULL) {
		perror("kaf.text.cpp");
		exit(1);
	}
	if ((specp = fopen("kaf.spec.cpp", "w")) == NULL) {
		perror("kaf.spec.cpp");
		exit(1);
	}
	if (!sourcefile)
		infile = stdin;
	else
		if ((infile = fopen(sourcefile, "r")) == NULL) {
			perror(sourcefile);
			exit(1);
		}
	fprintf(textp, "/* The user routine file. */\n\n");
	fprintf(specp, "/* The specification file. */\n\n");
	fprintf(specp, "#include \"kafgraf.h\"\n\n");
	return (0);
}
