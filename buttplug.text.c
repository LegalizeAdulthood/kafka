/* The user routine file. */



/*
 * buttplug -- a program to generate statements about buttplugs.
 *	Compile with etc.c, output.c, and maketext.c
 */

#include <stdio.h>
#include <ctype.h>

#define CH(n, o)	return (((rnum() % o) < n) ? 1 : 0)

rnum()
{
	return (random());
}

char *ones, *subject, *verb_adj;

#define YOUR	subject = "your", ones = "your", verb_adj = ""
#define MY	subject = "I", ones = "my", verb_adj = ""
#define HIS	subject = "he", ones = "his", verb_adj = "#s"
#define HER	subject = "she", ones = "her", verb_adj = "#s"
#define THEIR	subject = "they", ones = "their", verb_adj = ""

/* Instead of defining all these words as rules, keep arrays of them. We
 * can also make the insults more interesting by using alliteration on
 * the words...
 */

char *animals[] = { 	/* Animals. */
  "aardvark", "amphibian", "animal", "ant", "apteryx", "bird", "buzzard",
  "cat", "cockroach", "cow", "dodo", "dog", "duck", "emu", "fish", "flea",
  "frog", "gazelle", "gerbil", "goat", "goose", "grep", "haddock",
  "hippotomus", "hog", "horse", "insect", "jackal", "kitten", "kobold",
  "leech", "louse", "milkweed", "monkey", "moose", "mouse", "octopus",
  "penguin", "pig", "pigeon", "puppy", "racoon", "rat", "rust monster",
  "sheep", "skunk", "slime-mold", "slug", "snail", "snake", "squid", "toad",
  "tuna", "turkey", "turtle", "weed", "whale", "wombat", "worm", "yak",
  NULL
};

char *derogatory[] = {	/* Derogatory terms. */
  "airhead", "axe murderer", "beer", "bug-breath", "bum", "cookie", "creep",
  "cretin", "crud", "deviate", "dink", "dipstick", "dirt", "dork", "dude",
  "dumbbell", "fairy", "fleabag", "fruit", "garbage", "geek", "gimp", "glob",
  "gloop", "goober", "goof", "grunt", "gump", "hag", "idiot", "ignoramus",
  "inanimate object", "jerk", "lark's vomit", "lump", "lunkhead", "monster",
  "mudface", "mudpie", "muscle-brain", "nasty", "numskull", "nymphomaniac",
  "pervert", "pinhead", "plant", "plebe", "quiche-eater", "rat spit",
  "redneck", "scary dude", "scum that grows on the bottom of the lake",
  "scum", "septic tank", "slob", "super geek", "toady", "vegetable",
  "weight-lifter", "welfare mother", "wonderful, sensitive human being",
  NULL
};

char *body_parts[] = {	/* Body parts. */
  "behind", "brain", "crotch", "ear", "eye", "face", "liver", "nose",
  "pancreas", "private parts", "rectum", "stomach",
  NULL
};

char *objects[] = {	/* Objects. */
  "VAX", "baseball bat", "big thing", "boulder", "brick", "car",
  "heavy object", "knife", "manhole cover", "needle", "object", "rock",
  "sword", "terminal", "tree", "truck", "two by four", "colostomy bag",
  NULL
};

char *adjectives[] = {	/* Adjectives. */
  "Lovecraftian", "abnormal", "absurd", "awful", "bad", "bootlicking",
  "brainless", "cowardly", "crude", "dastardly", "dirty", "diseased",
  "disgusting", "disobedient", "dopey", "dumb", "elitist", "evil", "fat",
  "flabby", "foolish", "foul", "frightening", "funny", "furry", "green",
  "gruesome", "gumpy", "hairy", "hideous", "horrifying", "icky", "ignorant",
  "imaginary", "intolerable", "lousy", "ludicrous", "lumpy", "mangy", "muddy",
  "nauseating", "nauseating", "old", "pencil-necked", "perverted", "ratty",
  "religous", "ridiculous", "rotten", "scab-picking", "scummy", "sick",
  "silly", "skinny", "slimy", "slippery", "slobbering", "slow", "small",
  "smelly", "strange", "stupid", "trashy", "ugly", "undesirable", "unhappy",
  "unpleasant", "unspeakable", "unstructured", "uppity", "vile", "worthless",
  NULL
};

char *adverbs[] = {	/* Adverbs. */
  "disgustingly", "incredibly", "mega", "microscopically", "paradoxically",
  "phenomenally", "pseudo", "rather", "ridiculously", "semi", "slightly",
  "stupidly", "surprisingly", "terribly", "typically", "unbeliveably",
  NULL
};

char *nasties[] = {	/* Nasty things. */
  "abuse", "annihilate", "avoid", "behead", "chop up", "damage", "destroy",
  "discriminate against", "disembowel", "dismember", "dissect", "eat",
  "flush", "forget about", "frighten", "hit", "ignore", "insult", "kick",
  "look at", "molest", "mush", "puree", "scramble", "shred", "spit on",
  "squish", "stab", "step on",
  NULL
};

char *diseases[] = {	/* Diseases. */
  "bad breath", "gout", "leprosy", "malaria", "plague", "halitosis",
  NULL
};

char *lubes[] = {			/* butt plug lubricants */
  "motor oil", "vaseline", "mayonaisse", "mustard", "WD-40", "honey",
  "KY jelly", "AstroGlide", "spit", "sperm", "peanut butter", "snot",
  "blood plasma", "feces",
  NULL
};

char *plugs[] = {			/* butt plugs */
  "dildo", "buttplug", "vibrator", "banana", "zuchini", "squash",
  "rolling pin", "coke bottle", "gerbil", "hamster", "fist", "fecostalagmite",
  "fist", "eggplant",
  NULL
  };

char *orifice[] = {			/* available orifices */
  "anus", "asshole", "sphincter", "vagina", "urethra", "throat",
  "eye socket", "ear", "nostril", "skin pore", "sucking chest wound",
  "colostomy hole", "anal cavity", "trachiotomy hole", "rectum",
  "urethra",
  NULL
  };

char *insertions[] = {			/* insertion verbs */
  "insert", "ram", "jam", "shove", "push", "squick",
  NULL
  };

char *inserted[] = {			/* past-tense insertion verbs */
  "inserted", "rammed", "jammed", "shoved", "pushed", "squicked",
  NULL
  };

char *men[] = {				/* men subjects */
  "George Bush", "Bill Clinton", "Ross Perot", "Paul Tsongas", "Jerry Brown",
  "Ronald Reagan", "John Sununu", "Pat Robertson", "Jimmy Carter",
  "Jerry Ford", "Richard Nixon", "Ted Koppel", "Dick Van Dyke",
  "Dick Van Patten", "Ricardo Montalbon", "William Shatner", "Leanord Nemoy",
  "Arnold Schwarzenegger", "Billy Crystal", "Magic Johnson",
  "Wilt Chamberlain", "White Fag", "White Fag", "White Fag", "White Fag",
  "Saddam Hussein", "Osama bin Laden",
  NULL
  };

char *women[] = {			/* women subjects */
  "Barbara Bush", "Hillary Clinton", "Margot Perot", "Nancy Reagan",
  "Phylis Schlafly", "Mary Tyler Moore", 
  NULL
  };

char *groups[] = {			/* aggregate subjects */
  "Democrats", "Republicans", "Socialiasts", "hate-mongers", "racists",
  "sexists", "Communists", "Berkleyites", "Taliban",
  NULL
  };

char *stuck[] = {			/* wedged states */
  "stuck", "wedged", "rammed",
  NULL
  };

char *lastchoice = NULL;

/* Word types. */

#define ANIMAL		1
#define DER_TERM	2
#define BODYPART	3
#define OBJECT		4
#define ADJ		5
#define ADVERB		6
#define NASTY_THING	7
#define DISEASE		8
#define LUBES		9
#define ORIFICE		10
#define PLUGS		11
#define INSERT		12
#define MEN		13
#define WOMEN		14
#define GROUPS		15
#define STUCK		16
#define INSERTED	17

getword(type)
{
  char **wds;	
  int i = 0, j = 0, k;
  int alliterate = lastchoice ? (random() % 4) : 0;
  
  switch (type)
    {
    case ANIMAL:	wds = animals; break;
    case DER_TERM:	wds = derogatory; break;
    case BODYPART:	wds = body_parts; break;
    case OBJECT:	wds = objects; break;
    case ADJ:		wds = adjectives; break;
    case ADVERB:	wds = adverbs; break;
    case NASTY_THING:	wds = nasties; break;
    case DISEASE:	wds = diseases; break;
    case LUBES:		wds = lubes; break;
    case PLUGS:		wds = plugs; break;
    case ORIFICE:	wds = orifice; break;
    case INSERT:	wds = insertions; break;
    case MEN:		wds = men; break;
    case WOMEN:		wds = women; break;
    case GROUPS:	wds = groups; break;
    case STUCK:		wds = stuck; break;
    case INSERTED:	wds = inserted; break;

    default:
      fprintf(stderr, "Bad thing %d\n", type);
    }
  
  /* See how many words there are that we can use. */
  for (k = 0; wds[k]; k++)
    if (alliterate && (*wds[k] == *lastchoice))
      j++;

  i = k;
  if (j == 0)
    {
    hoho:
      i = rnum() % i;
      lastchoice = wds[i];
      return ((int) wds[i]);
    }
  else
    {
      j = rnum() % j;
      for (k = 0; ; k++)
	if (*wds[k] == (isupper(*lastchoice) ?
			tolower(*lastchoice) : *lastchoice))
	  {
	    if (wds[k] == lastchoice)
	      goto hoho;
	    if (j == 0)
	      {
		lastchoice = wds[k];
		return ((int) wds[k]);
	      }
	    else
	      j--;
	  }
    }
}

_kkFunc1 ()
{
 CH(1,15); }
_kkFunc2 ()
{
 CH(1,20); }
_kkFunc3 ()
{
 CH(1,20); }
_kkFunc4 ()
{
 CH(1,50); }
_kkFunc5 ()
{
 CH(1,20); }
_kkFunc6 ()
{
 CH(1,20); }
_kkFunc7 ()
{
 CH(1,15); }
_kkFunc8 ()
{
 CH(1,20); }
_kkFunc9 ()
{
 CH(1,20); }
_kkFunc10 ()
{
 CH(1,20); }
_kkFunc11 ()
{
 CH(1,20); }
_kkFunc12 ()
{
 CH(1,20); }
_kkFunc13 ()
{
 CH(1,2); }
_kkFunc14 ()
{
 CH(1,2); }
_kkFunc15 ()
{
 HIS; CH(1,20); }
_kkFunc16 ()
{
 HER; CH(1,20); }
_kkFunc17 ()
{
 MY; CH(1,20); }
_kkFunc18 ()
{
 YOUR; CH(1,20); }
_kkFunc19 ()
{
 THEIR; }
_kkFunc20 ()
{
 return ((int) subject); }
_kkFunc21 ()
{
 return ((int) verb_adj); }
_kkFunc22 ()
{
 CH(1,20); }
_kkFunc23 ()
{
 CH(1,20); }
_kkFunc24 ()
{
 CH(1,20); }
_kkFunc25 ()
{
 CH(1,20); }
_kkFunc26 ()
{
 CH(1,20); }
_kkFunc27 ()
{
 CH(1,20); }
_kkFunc28 ()
{
 CH(1,20); }
_kkFunc29 ()
{
 CH(1,20); }
_kkFunc30 ()
{
 CH(1,20); }
_kkFunc31 ()
{
 CH(1,20); }
_kkFunc32 ()
{
 CH(1,20); }
_kkFunc33 ()
{
 CH(1,20); }
_kkFunc34 ()
{
 CH(1,20); }
_kkFunc35 ()
{
 CH(1,20); }
_kkFunc36 ()
{
 CH(1,20); }
_kkFunc37 ()
{
 CH(1,20); }
_kkFunc38 ()
{
 CH(1,20); }
_kkFunc39 ()
{
 CH(1,20); }
_kkFunc40 ()
{
 return (getword(STUCK)); }
_kkFunc41 ()
{
 CH(1,20); }
_kkFunc42 ()
{
 CH(1,20); }
_kkFunc43 ()
{
 return (getword(MEN)); }
_kkFunc44 ()
{
 return (getword(WOMEN)); }
_kkFunc45 ()
{
 return (getword(GROUPS)); }
_kkFunc46 ()
{
 return (getword(LUBES)); }
_kkFunc47 ()
{
 CH(1,20); }
_kkFunc48 ()
{
 CH(1,20); }
_kkFunc49 ()
{
 return (getword(PLUGS)); }
_kkFunc50 ()
{
 return (getword(ORIFICE)); }
_kkFunc51 ()
{
 return (getword(INSERT)); }
_kkFunc52 ()
{
 return (getword(INSERTED)); }
_kkFunc53 ()
{
 CH(1,20); }
_kkFunc54 ()
{
 CH(1,20); }
_kkFunc55 ()
{
 CH(1,20); }
_kkFunc56 ()
{
 CH(1,20); }
_kkFunc57 ()
{
 CH(1, 3); }
_kkFunc58 ()
{
 return (getword(ANIMAL)); }
_kkFunc59 ()
{
 CH(1, 10); }
_kkFunc60 ()
{
 CH(1, 10); }
_kkFunc61 ()
{
 CH(1, 40); }
_kkFunc62 ()
{
 CH(1, 40); }
_kkFunc63 ()
{
 CH(1, 40); }
_kkFunc64 ()
{
 CH(1, 40); }
_kkFunc65 ()
{
 CH(1, 40); }
_kkFunc66 ()
{
 CH(1, 40); }
_kkFunc67 ()
{
 CH(1, 40); }
_kkFunc68 ()
{
 CH(1,40); }
_kkFunc69 ()
{
 return (getword(ADJ)); }
_kkFunc70 ()
{
 CH(1, 50); }
_kkFunc71 ()
{
 return (getword(ADVERB)); }
_kkFunc72 ()
{
 CH(2, 3); }
_kkFunc73 ()
{
 return (getword(DISEASE)); }
_kkFunc74 ()
{
 CH(1, 10); }
_kkFunc75 ()
{
 return (getword(BODYPART)); }
_kkFunc76 ()
{
 CH(1, 5); }
_kkFunc77 ()
{
 CH(1, 15); }
_kkFunc78 ()
{
 CH(1, 15); }
_kkFunc79 ()
{
 return (getword(OBJECT)); }
_kkFunc80 ()
{
 lastchoice = NULL; return (1); }
_kkFunc81 ()
{
 lastchoice = NULL; return (1); }
_kkFunc82 ()
{
 lastchoice = NULL; return (1); }
_kkFunc83 ()
{
 return ((int) ones); }