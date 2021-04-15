#ifdef __cplusplus
#include <stdio.h>
    extern "C" {
	extern void yyerror(char *);
	extern int yylex();
    }
#endif /* __cplusplus */ 

# line 2 "parse.y"

/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher 
 *	Permission is granted to do anything with this code except sell it
 *	or remove this message.
 *
 * The Kafka parser. It is called once, and builds the
 * necessary data structures for the specification. 
 */

#include <stdio.h>
#include <strings.h>
#include "kafgraf.h"

char buf[BUFSIZ];
extern FILE *inp;
extern struct karc *avarc;

# define LBRACE 257
# define RBRACE 258
# define NONTERM 259
# define TERM 260
# define RULEOP 261
# define SSEP 262
# define KESC 263
# define COPEN 264
# define CCLOSE 265
# define SEMI 266
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 107 "parse.y"


short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 19
# define YYLAST 21
short yyact[]={

  17,   3,   5,   6,  11,  13,  18,  10,  20,  21,
  15,  19,  16,  14,  12,   9,   4,   8,   7,   2,
   1 };
short yypact[]={

-1000,-1000,-261,-1000,-1000,-1000,-1000,-255,-1000,-1000,
-1000,-1000,-256,-247,-266,-1000,-251,-1000,-1000,-1000,
-1000,-1000 };
short yypgo[]={

   0,  20,  19,  18,  17,  16,  15,  14,  13,  12,
  11 };
short yyr1[]={

   0,   1,   4,   4,   2,   2,   5,   5,   3,   3,
   7,   6,   8,   8,   8,   9,   9,  10,  10 };
short yyr2[]={

   0,   4,   0,   1,   0,   2,   1,   1,   0,   2,
   0,   5,   1,   2,   1,   0,   2,   1,   1 };
short yychk[]={

-1000,  -1,  -2, 262,  -5, 263, 264,  -3,  -4,  -6,
 262, 259,  -7, 261,  -8, 257,  -9, 266, 257, -10,
 259, 260 };
short yydef[]={

   4,  -2,   0,   8,   5,   6,   7,   2,   1,   9,
   3,  10,   0,  15,   0,  12,  14,  11,  13,  16,
  17,  18 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar	4.1	(Berkeley)	2/11/83";
#endif /* not lint */

#
# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

	short yys[YYMAXDEPTH];
	short yyj, yym;
	register YYSTYPE *yypvt;
	register short yystate, *yyps, yyn;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

 yystack:    /* put a state and value onto the stack */

#ifdef YYDEBUG
	if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
		if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
		*yyps = yystate;
		++yypv;
		*yypv = yyval;

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
		}

 yydefault:
	/* default state action */

	if( (yyn=yydef[yystate]) == -2 ) {
		if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
		/* look through exception table */

		for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
			}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
		}

	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yyerrflag ){

		case 0:   /* brand new error */

			yyerror( "syntax error" );
		yyerrlab:
			++yynerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yyps >= yys ) {
			   yyn = yypact[*yyps] + YYERRCODE;
			   if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
			      yystate = yyact[yyn];  /* simulate a shift of "error" */
			      goto yystack;
			      }
			   yyn = yypact[*yyps];

			   /* the current yyps has no shift onn "error", pop stack */

#ifdef YYDEBUG
			   if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
			   --yyps;
			   --yypv;
			   }

			/* there is no state on the stack with an error shift ... abort */

	yyabort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#ifdef YYDEBUG
			if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */

			}

		}

	/* reduction by production yyn */

#ifdef YYDEBUG
		if( yydebug ) printf("reduce %d\n",yyn);
#endif
		yyps -= yyr2[yyn];
		yypvt = yypv;
		yypv -= yyr2[yyn];
		yyval = yypv[1];
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
		switch(yym){
			
case 3:
# line 38 "parse.y"
{	/* Deal with program section here. */ 
			int n;
			extern FILE *textp;

			do {
				n = fread(buf, 1, BUFSIZ, inp);
				fwrite(buf, 1, n, textp);
			} while (n == BUFSIZ);
			} break;
case 6:
# line 53 "parse.y"
{ /* Deal with Kafka escape here. 
			  * (None yet implemented.) 
			  */ 
			} break;
case 7:
# line 57 "parse.y"
{ /* Copy C code here. */ 
			copyccode();
			} break;
case 10:
# line 67 "parse.y"
{ 	/* Got the NT name. Create a node. */
			newrule(yypvt[-0]);
			} break;
case 12:
# line 73 "parse.y"
{	/* A computed terminal. */
			docompterm();
			} break;
case 13:
# line 77 "parse.y"
{	/* We have to copy the C code and clean up. */
			int fnum;
			extern struct knode *n;
			
			fnum = newnum();
			transcribe(fnum);
			n->kn_fnum = fnum;
			avarc->ka_narc = NULL;
			} break;
case 14:
# line 86 "parse.y"
{	/* Just clean up. */
			extern struct knode *n;

			n->kn_fnum = 0;
			avarc->ka_narc = NULL;
			} break;
case 17:
# line 98 "parse.y"
{
			dononterm(yypvt[-0]);
			} break;
case 18:
# line 102 "parse.y"
{
			doterm(yypvt[-0]);
			} break;
		}
		goto yystack;  /* stack new state and value */

	}
