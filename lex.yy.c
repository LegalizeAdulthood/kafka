# include "stdio.h"
#ifdef __cplusplus
    extern "C" {
	extern int yyreject();
	extern int yywrap();
	extern int yylook();
	extern void main();
	extern int yyback(int *, int);
	extern int yyinput();
	extern void yyoutput(int);
	extern void yyunput(int);
	extern int yylex();
    }
#endif /* __cplusplus */
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin ={stdin}, *yyout ={stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

/* RCS Info: $Revision: $ on $Date: $
 *           $Source: $
 * Copyright (c) 1985 Wayne A. Christopher 
 *	Permission is granted to do anything with this code except sell it
 *	or remove this message.
 *
 * The lexical analyzer for kafka.
 */

#include "y.tab.h"

char lookahead[100];	/* For pushback of characters. */
int nlk = 0;		/* # characters pushed back. */
extern FILE *inp;	/* The input file. */
extern int yylval;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
	{ /* A non-terminal. */
			yytext[yyleng - 1] = '\0';
			yylval = (int) (yytext + 1);
			return (NONTERM);
			}
break;
case 2:
	{ /* White space. */
			}
break;
case 3:
		{ /* A comment. Ignore. */
			}
break;
case 4:
{ /* An unquoted terminal string. */
			yylval = (int) yytext;
			return (TERM);
			}
break;
case 5:
	{ /* A quoted terminal. */
			yytext[yyleng - 1] = '\0';
			yylval = (int) (yytext + 1);
			return (TERM);
			}
break;
case 6:
		{ /* The rule operator. */
			return (RULEOP);
			}
break;
case 7:
		{ /* The section seperator. */
			return (SSEP);
			}
break;
case 8:
	{ /* A kafka escape. */
			yylval = (int) yytext[1];
			return (KESC);
			}
break;
case 9:
		{ /* Begin def section C code. */
			return (COPEN);
			}
break;
case 10:
		{ /* End def section C code. */
			return (CCLOSE);
			}
break;
case 11:
		{ /* Open brace. */
			return (LBRACE);
			}
break;
case 12:
		{ /* Close brace. */
			return (RBRACE);
			}
break;
case 13:
		{ /* Semicolon. */
			return (SEMI);
			}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

/* The redefined input and unput functions -- they must be usable by
 * other routines. 
 */

int lineno = 0;

char input()
{
	int c;
	if (nlk == 0) {
		c = getc(inp);
		if (c == '\n') 
			lineno++;
		if (c == EOF) 
			return (0);
		else
			return (c);
	} else {
		c = lookahead[--nlk];
		return (c);
	}
}

unput(c)
char c;
{
	lookahead[nlk++] = c;
	return;
}

/* Don't need this thing... */

yywrap()
{
	return (1);
}

int yyvstop[] ={
0,

2,
4,
0,

2,
4,
0,

4,
0,

2,
0,

13,
0,

6,
0,

11,
0,

12,
0,

4,
-3,
0,

5,
0,

1,
0,

-3,
0,

3,
0,

7,
0,

-8,
0,

9,
0,

10,
0,

8,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,4,	
15,15,	4,4,	4,4,	5,5,	
0,0,	0,0,	0,0,	7,7,	
0,0,	3,0,	3,0,	5,5,	
5,5,	0,0,	0,0,	7,0,	
7,0,	0,0,	0,0,	14,0,	
14,0,	0,0,	0,0,	1,5,	
4,4,	0,0,	1,0,	0,0,	
0,0,	0,0,	0,0,	2,11,	
3,0,	2,12,	3,0,	0,0,	
5,13,	3,0,	7,0,	5,5,	
7,7,	0,0,	14,0,	7,7,	
11,11,	0,0,	0,0,	0,0,	
1,6,	1,7,	1,8,	1,0,	
11,15,	11,16,	1,3,	2,6,	
2,7,	2,8,	2,0,	3,0,	
3,0,	3,0,	3,0,	0,0,	
15,15,	0,0,	0,0,	5,5,	
7,14,	0,0,	0,0,	7,7,	
14,14,	0,0,	0,0,	0,0,	
0,0,	11,15,	0,0,	0,0,	
11,15,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	12,17,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
11,11,	0,0,	0,0,	0,0,	
1,9,	0,0,	1,10,	0,0,	
0,0,	0,0,	0,0,	2,9,	
0,0,	2,10,	0,0,	3,0,	
0,0,	3,0,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,18,	12,18,	12,18,	12,18,	
12,19,	18,18,	12,20,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	18,18,	18,21,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	18,18,	0,0,	
0,0,	18,18,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	18,18,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,
yycrank+-8,	yysvec+1,	yyvstop+4,
yycrank+-12,	yysvec+1,	yyvstop+7,
yycrank+4,	0,		yyvstop+9,
yycrank+-14,	0,		0,	
yycrank+0,	0,		yyvstop+11,
yycrank+-18,	0,		0,	
yycrank+0,	0,		yyvstop+13,
yycrank+0,	0,		yyvstop+15,
yycrank+0,	0,		yyvstop+17,
yycrank+-55,	0,		yyvstop+19,
yycrank+73,	0,		0,	
yycrank+0,	0,		yyvstop+22,
yycrank+-22,	yysvec+7,	yyvstop+24,
yycrank+-11,	yysvec+11,	yyvstop+26,
yycrank+0,	0,		yyvstop+28,
yycrank+0,	0,		yyvstop+30,
yycrank+-196,	0,		yyvstop+32,
yycrank+0,	0,		yyvstop+34,
yycrank+0,	0,		yyvstop+36,
yycrank+0,	0,		yyvstop+38,
0,	0,	0};
struct yywork *yytop = yycrank+261;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,'%' ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,'%' ,'%' ,'%' ,'%' ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'%' ,01  ,'%' ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,1,0,0,0,0,
1,0,0,0,0,0,0,0,
0};
/*	ncform	4.1	83/08/11	*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__STDC__) || defined(__cplusplus)
yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
#if defined(__STDC__) || defined(__cplusplus)
void yyoutput(int c) {
#else
yyoutput(c)
  int c; {
#endif
	output(c);
	}
#if defined(__STDC__) || defined(__cplusplus)
void yyunput(int c) {
#else
yyunput(c)
   int c; {
#endif
	unput(c);
	}
