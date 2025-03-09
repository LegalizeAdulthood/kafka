%{

/*
 * buttplug -- a program to generate statements about buttplugs.
 *      Compile with etc.c, output.c, and maketext.c
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "runtime.h"

const char *ones, *subject, *verb_adj;

#define YOUR    subject = "your", ones = "your", verb_adj = ""
#define MY      subject = "I", ones = "my", verb_adj = ""
#define HIS     subject = "he", ones = "his", verb_adj = "#s"
#define HER     subject = "she", ones = "her", verb_adj = "#s"
#define THEIR   subject = "they", ones = "their", verb_adj = ""

/* Instead of defining all these words as rules, keep arrays of them. We
 * can also make the insults more interesting by using alliteration on
 * the words...
 */

const char *animals[] = {     /* Animals. */
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

const char *derogatory[] = {  /* Derogatory terms. */
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

const char *body_parts[] = {  /* Body parts. */
  "behind", "brain", "crotch", "ear", "eye", "face", "liver", "nose",
  "pancreas", "private parts", "rectum", "stomach",
  NULL
};

const char *objects[] = {     /* Objects. */
  "VAX", "baseball bat", "big thing", "boulder", "brick", "car",
  "heavy object", "knife", "manhole cover", "needle", "object", "rock",
  "sword", "terminal", "tree", "truck", "two by four", "colostomy bag",
  NULL
};

const char *adjectives[] = {  /* Adjectives. */
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

const char *adverbs[] = {     /* Adverbs. */
  "disgustingly", "incredibly", "mega", "microscopically", "paradoxically",
  "phenomenally", "pseudo", "rather", "ridiculously", "semi", "slightly",
  "stupidly", "surprisingly", "terribly", "typically", "unbeliveably",
  NULL
};

const char *nasties[] = {     /* Nasty things. */
  "abuse", "annihilate", "avoid", "behead", "chop up", "damage", "destroy",
  "discriminate against", "disembowel", "dismember", "dissect", "eat",
  "flush", "forget about", "frighten", "hit", "ignore", "insult", "kick",
  "look at", "molest", "mush", "puree", "scramble", "shred", "spit on",
  "squish", "stab", "step on",
  NULL
};

const char *diseases[] = {    /* Diseases. */
  "bad breath", "gout", "leprosy", "malaria", "plague", "halitosis",
  NULL
};

const char *lubes[] = {                       /* butt plug lubricants */
  "motor oil", "vaseline", "mayonaisse", "mustard", "WD-40", "honey",
  "KY jelly", "AstroGlide", "spit", "sperm", "peanut butter", "snot",
  "blood plasma", "feces",
  NULL
};

const char *plugs[] = {                       /* butt plugs */
  "dildo", "buttplug", "vibrator", "banana", "zuchini", "squash",
  "rolling pin", "coke bottle", "gerbil", "hamster", "fist", "fecostalagmite",
  "fist", "eggplant",
  NULL
  };

const char *orifice[] = {                     /* available orifices */
  "anus", "asshole", "sphincter", "vagina", "urethra", "throat",
  "eye socket", "ear", "nostril", "skin pore", "sucking chest wound",
  "colostomy hole", "anal cavity", "trachiotomy hole", "rectum",
  "urethra",
  NULL
  };

const char *insertions[] = {                  /* insertion verbs */
  "insert", "ram", "jam", "shove", "push", "squick",
  NULL
  };

const char *inserted[] = {                    /* past-tense insertion verbs */
  "inserted", "rammed", "jammed", "shoved", "pushed", "squicked",
  NULL
  };

const char *men[] = {                         /* men subjects */
  "George Bush", "Bill Clinton", "Ross Perot", "Paul Tsongas", "Jerry Brown",
  "Ronald Reagan", "John Sununu", "Pat Robertson", "Jimmy Carter",
  "Jerry Ford", "Richard Nixon", "Ted Koppel", "Dick Van Dyke",
  "Dick Van Patten", "Ricardo Montalbon", "William Shatner", "Leanord Nemoy",
  "Arnold Schwarzenegger", "Billy Crystal", "Magic Johnson",
  "Wilt Chamberlain", "White Fag", "White Fag", "White Fag", "White Fag",
  "Saddam Hussein", "Osama bin Laden",
  NULL
  };

const char *women[] = {                       /* women subjects */
  "Barbara Bush", "Hillary Clinton", "Margot Perot", "Nancy Reagan",
  "Phylis Schlafly", "Mary Tyler Moore", 
  NULL
  };

const char *groups[] = {                      /* aggregate subjects */
  "Democrats", "Republicans", "Socialiasts", "hate-mongers", "racists",
  "sexists", "Communists", "Berkleyites", "Taliban",
  NULL
  };

const char *stuck[] = {                       /* wedged states */
  "stuck", "wedged", "rammed",
  NULL
  };

/* Word types. */

#define ANIMAL          1
#define DER_TERM        2
#define BODYPART        3
#define OBJECT          4
#define ADJ             5
#define ADVERB          6
#define NASTY_THING     7
#define DISEASE         8
#define LUBES           9
#define ORIFICE         10
#define PLUGS           11
#define INSERT          12
#define MEN             13
#define WOMEN           14
#define GROUPS          15
#define STUCK           16
#define INSERTED        17

int getword(int type)
{
  const char **wds;   
  
  switch (type)
    {
    case ANIMAL:        wds = animals; break;
    case DER_TERM:      wds = derogatory; break;
    case BODYPART:      wds = body_parts; break;
    case OBJECT:        wds = objects; break;
    case ADJ:           wds = adjectives; break;
    case ADVERB:        wds = adverbs; break;
    case NASTY_THING:   wds = nasties; break;
    case DISEASE:       wds = diseases; break;
    case LUBES:         wds = lubes; break;
    case PLUGS:         wds = plugs; break;
    case ORIFICE:       wds = orifice; break;
    case INSERT:        wds = insertions; break;
    case MEN:           wds = men; break;
    case WOMEN:         wds = women; break;
    case GROUPS:        wds = groups; break;
    case STUCK:         wds = stuck; break;
    case INSERTED:      wds = inserted; break;

    default:
      fprintf(stderr, "Bad thing %d\n", type);
    }

  return random_word(wds);
}

%}

%%

<start>         = <buttplug> ;

<buttplug> = <exclam> <ep> { CH(1,15); };
<buttplug> = <sentence> <pp> { CH(1,20); };
<buttplug> = <question> <qp> { CH(1,20); };
<buttplug> = <buttplug>;

<exclam> = buttplug { CH(1,50); };
<exclam> = <lube-plug> and <plug-orifice> { CH(1,20); };
<exclam> = <lube-orifice> and <insert-plug> { CH(1,20); };
<exclam> = <exclam>;

<sentence> = <subject> "could plug a" <animalp> "with a" <plugp> { CH(1,15); };
<sentence> = <subject> wonder <verb-adj> "how a" <plugp> in <ones> <orifice>
        "would feel" { CH(1,20); };
<sentence> = <subject> "often wonder" <verb-adj> "what a" <plugp>
        "would feel like in" <ones> <orifice> { CH(1,20); };
<sentence> = <subject> like <verb-adj> "the feeling of a" <plugp> in <ones>
        <orifice> { CH(1,20); };
<sentence> = <single-subject> "has a" <plugp> <stuck> in <ones> <orifice>
        and <subj-ref> "can't get it out" { CH(1,20); };
<sentence> = <plural-subject> "have a" <plugp> up <ones> <orifice> and
        <subj-ref> "can't get it out" { CH(1,20); };
<sentence> = <sentence>;

<subject> = <single-subject> { CH(1,2); };
<subject> = <plural-subject> { CH(1,2); };
<subject> = <subject>;

<single-subject> = <man> { HIS; CH(1,20); };
<single-subject> = <woman> { HER; CH(1,20); };
<single-subject> = I { MY; CH(1,20); };
<single-subject> = you { YOUR; CH(1,20); };
<single-subject> = <single-subject>;

<plural-subject> = <groups> { THEIR; return 1; };

<subj-ref> = { return 1; };
<verb-adj> = { return 1; };

<question> = "would you like a" <plugp> <past-insert-action> "in your"
        <orifice> { CH(1,20); };
<question> = "who will" <lube-plug> and <plug-orifice> { CH(1,20); };
<question> = <question>;

<lube-plug> = "cover the" <plugp> with <lube> { CH(1,20); };
<lube-plug> = "smother the" <plugp> with <lube> { CH(1,20); };
<lube-plug> = "grease the" <plugp> with <lube> { CH(1,20); };
<lube-plug> = "dip the" <plugp> in <lube> { CH(1,20); };
<lube-plug> = "immerse the" <plugp> in <lube> { CH(1,20); };
<lube-plug> = "ladle the" <lube> "over the" <plugp> { CH(1,20); };
<lube-plug> = "pour the" <lube> "onto the" <plugp> { CH(1,20); };
<lube-plug> = "spit the" <lube> "on the" <plugp> { CH(1,20); };
<lube-plug> = "spread the" <lube> "on the" <plugp> { CH(1,20); };
<lube-plug> = <lube-plug>;

<lube-orifice> = "cover the" <orifice> with <lube> { CH(1,20); };
<lube-orifice> = "smother the" <orifice> with <lube> { CH(1,20); };
<lube-orifice> = "grease the" <orifice> with <lube> { CH(1,20); };
<lube-orifice> = "immerse the" <orifice> in <lube> { CH(1,20); };
<lube-orifice> = "pour the" <lube> "onto the" <orifice> { CH(1,20); };
<lube-orifice> = "spit the" <lube> "on the" <orifice> { CH(1,20); };
<lube-orifice> = "spread the" <lube> "on the" <orifice> { CH(1,20); };
<lube-orifice> = <lube-orifice>;

<stuck> = { return (getword(STUCK)); };
<person> = <man> { CH(1,20); };
<person> = <woman> { CH(1,20); };
<person> = <person>;

<man> = { return (getword(MEN)); };
<woman> = { return (getword(WOMEN)); };

<groups> = { return (getword(GROUPS)); };

<lube> = { return (getword(LUBES)); };

<plug-orifice> = <insert-action> "it in your" <orifice> { CH(1,20); };
<plug-orifice> = <insert-action> "it in someone else's" <orifice>
        { CH(1,20); };
<plug-orifice> = <plug-orifice>;

<insert-plug> = <insert-action> the <plugp> "into it";
<insert-plug> = <insert-action> the <plugp> inside;

<plugp> = <adjp> <plugs>;
<plugs> = { return (getword(PLUGS)); };

<orifice> = { return (getword(ORIFICE)); };

<insert> = { return (getword(INSERT)); };

<inserted> = { return (getword(INSERTED)); };

<past-insert-action> = <inserted> { CH(1,20); };
<past-insert-action> = <adverb> <inserted> { CH(1,20); };
<past-insert-action> = <past-insert-action>;

<insert-action> = <insert> { CH(1,20); };
<insert-action> = <adverb> <insert> { CH(1,20); };
<insert-action> = <insert-action>;

<animalp>       = <adjp> <animal> { CH(1, 3); };
<animalp>       = <animal> ;

<animal>        = { return (getword(ANIMAL)); };

<adjp>          = <adverb> <adj>        { CH(1, 10); };
<adjp>          = <adj> <adj> { CH(1, 10); };
<adjp>          = <adj> ;

<adj>           = <animal> "#-infested" { CH(1, 40); };
<adj>           = <animal> "#ish" { CH(1, 40); };
<adj>           = <noun> "#-loving" { CH(1, 40); };
<adj>           = <noun> "#-eating" { CH(1, 40); };
<adj>           = <noun> "#like" { CH(1, 40); };
<adj>           = <disease> "#-infested" { CH(1, 40); };
<adj>           = <animal> <bodypart> "#ed" { CH(1, 40); };
<adj>           = <lube> "#-covered" { CH(1,40); };
<adj>           = <adj-x> ;

<adj-x>         = { return (getword(ADJ)); };

<adverb>        = <adj> "#ly" { CH(1, 50); };
<adverb>        = <adverb-x> ;

<adverb-x>      = { return (getword(ADVERB)); };

<noun>          = <animal>      { CH(2, 3); };
<noun>          = <object> ;

<disease>       = { return (getword(DISEASE)); };

<bodypart>      = <adjp> <bodypart> { CH(1, 10); };
<bodypart>      = <bodypart-x> ;

<bodypart-x>    = { return (getword(BODYPART)); };

<object>        = <animalp> { CH(1, 5); };
<object>        = "pile of" <thing> "#s" { CH(1, 15); };
<object>        = "bunch of" <thing> "#s" { CH(1, 15); };
<object>        = <plugs>;
<object>        = <object-x> ;

<object-x>      = { return (getword(OBJECT)); };

<thing>         = <noun> ;

<pp>            = . { g_last_choice = nullptr; return (1); };
<ep>            = ! { g_last_choice = nullptr; return (1); };
<qp>            = ? { g_last_choice = nullptr; return (1); };

<ones>          = { return 1; } ;
