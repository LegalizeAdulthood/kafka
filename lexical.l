%{

/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher 
 *	Permission is granted to do anything with this code except sell it
 *	or remove this message.
 *
 * The lexical analyzer for kafka.
 */

#include "kafka_parser.h"
#include "init.h"
#include <stdexcept>

char lookahead[100];	/* For pushback of characters. */
int nlk = 0;		/* # characters pushed back. */
extern FILE *infile;	/* The input file. */
extern char *yylval;

#ifdef _WIN32
inline int isatty(int n)
{
    return 1;
}
#endif

%}

%%

\<[^ \t\n]*\>		{ /* A non-terminal. */
			yytext[yyleng - 1] = '\0';
			yylval = (yytext + 1);
			return NONTERM;
			}

[ \t\n]*		{ /* White space. */
			}

^#.*$			{ /* A comment. Ignore. */
			}

[^ \"\t\n=\<\>;\{\}\%]*	{ /* An unquoted terminal string. */
			yylval = yytext;
			return TERM;
			}

\"[^\"]*\"		{ /* A quoted terminal. */
			yytext[yyleng - 1] = '\0';
			yylval = (yytext + 1);
			return TERM;
			}

=			{ /* The rule operator. */
			return RULEOP;
			}

^\%\%			{ /* The section seperator. */
			return SSEP;
			}

^\%[A-Za-z].*$		{ /* A kafka escape. */
			yylval = &yytext[1];
			return KESC;
			}

^\%\{			{ /* Begin def section C code. */
			return COPEN;
			}

^\%\}			{ /* End def section C code. */
			return CCLOSE;
			}

\{			{ /* Open brace. */
			return LBRACE;
			}

\}			{ /* Close brace. */
			return RBRACE;
			}

\;			{ /* Semicolon. */
			return SEMI;
			}


%%

/* The redefined input and unput functions -- they must be usable by
 * other routines. 
 */

int lex_input()
{
    return yyinput();
}

void lex_unput(char c)
{
    yyunput( c, (yytext_ptr)  );
}

/* Don't need this thing... */

int yywrap()
{
    return 1;
}
