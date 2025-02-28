
# RCS Info: $Revision: $ on $Date: $
#           $Source: $
# Copyright (c) 1985 Wayne A. Christopher 
#       Permission is granted to do anything with this code except sell it
#       or remove this message.
#
# The following program is written in 'kafka', a sort of BNF with imbedded
# C code that directs the selection of rules. (CH(x,y) is a macro that
# means basically "accept this rule x out of y times".) Otherwise rules
# are checked from top to bottom.  The program that takes this specification
# and turns it into a C program (which then spits out strings) can be found
# in ~/bin/kafka, and the source and other useful things can be found in
# ~/kafka. (Some on ernie, in ~faustus/kafka.)
# The program should be pretty self-explanatory, though -- it is
# supposed to look a bit like lex and yacc specifications...
# By the way, rules are written <non-terminal> = stuff { C code } ;
# where the stuff can be any mix of non-termnals (surrounded by <>) and
# terminals. The C code should return (1) if the rule is to be used and 0
# if not. If there is no stuff, the C code can return a pointer to a string
# that is taken to be a terminal, but I'm not using this because it isn't
# very neat and is only useful when you are doing non-context free stuff...

%{

#include <stdlib.h>

inline int CH(int n, int o)
{
    return (rand() - 1313513) % o < n ? 1 : 0;
}

/* I think there used to be a reason for doing ^^^ this... */

%}

%%

<start>         = <unit>                                ;

<unit>          = <s> "."                               { return CH(3, 4); } ;
<unit>          = <rnd>                                 ;

# We have to be explicit about what kind of nouns go with what verbs.

<s>             = <s> , <Conj> <s>                      { return CH(1, 25); } ;

# verb1 is sort of simple physical stuff (transitive), non-intentional.
<s>             = <thing> <verb1> <thing>               { return CH(1, 20); } ;

<verb1>         = "fell on"                             { return CH(1, 20); } ;
<verb1>         = was <in-rel-to>                       { return CH(1, 20); } ;
<verb1>         = hit                                   { return CH(1, 20); } ;
<verb1>         = "was in fact"                         { return CH(1, 20); } ;
<verb1>         = "was almost as" <adj1> as             { return CH(1, 20); } ;
<verb1>         = "was as" <adj1> as                    { return CH(1, 20); } ;
<verb1>         = "was more" <adj1> than                { return CH(1, 20); } ;
<verb1>         = "may have been" <in-rel-to>           { return CH(1, 20); } ;
<verb1>         = "looked like"                         { return CH(1, 20); } ;
<verb1>         = reminded <agent> of                   { return CH(1, 20); } ;
<verb1>         = "seemed to be"                        { return CH(1, 20); } ;
<verb1>         = <verb1>                               ;

# verb2 is intransitive sorts of things, and complex transitive verbs.
<s>             = <agent> <verb2>                       { return CH(1, 20); } ;

<verb2>         = said "'" <s> "'"                      { return CH(1, 20); } ;
<verb2>         = "said that" <s>                       { return CH(1, 20); } ;
<verb2>         = ran                                   { return CH(1, 20); } ;
<verb2>         = died                                  { return CH(1, 20); } ;
<verb2>         = exploded                              { return CH(1, 20); } ;
<verb2>         = ate                                   { return CH(1, 20); } ;
<verb2>         = became <adj1>                         { return CH(1, 20); } ;
<verb2>         = was <adj1>                            { return CH(1, 8); } ;
<verb2>         = seemed <adj1>                         { return CH(1, 10); } ;
<verb2>         = jumped                                { return CH(1, 20); } ;
<verb2>         = walked                                { return CH(1, 20); } ;
<verb2>         = fell                                  { return CH(1, 20); } ;
<verb2>         = disappeared                           { return CH(1, 20); } ;
<verb2>         = "hopped around"                       { return CH(1, 20); } ;
<verb2>         = flew                                  { return CH(1, 20); } ;
<verb2>         = used <thing> "as a" <Inan-obj>        { return CH(1, 20); } ;
<verb2>         = gave <thing> to <agent>               { return CH(1, 20); } ;
<verb2>         = "bit the dust"                        { return CH(1, 20); } ;
<verb2>         = <verb2>                               ;

# verb3 is transitive intentional things.
<s>             = <agent> <adv> <verb3> <thing>         { return CH(1, 5); } ;

<verb3>         = hit                                   { return CH(1, 20); } ;
<verb3>         = used                                  { return CH(1, 20); } ;
<verb3>         = "acted like"                          { return CH(1, 20); } ;
<verb3>         = "thought he was"                      { return CH(1, 20); } ;
<verb3>         = "looked like"                         { return CH(1, 20); } ;
<verb3>         = ate                                   { return CH(1, 20); } ;
<verb3>         = "threw out"                           { return CH(1, 20); } ;
<verb3>         = "looked at"                           { return CH(1, 20); } ;
<verb3>         = disliked                              { return CH(1, 20); } ;
<verb3>         = "cooked and ate"                      { return CH(1, 20); } ;
<verb3>         = destroyed                             { return CH(1, 20); } ;
<verb3>         = lifted                                { return CH(1, 20); } ;
<verb3>         = stole                                 { return CH(1, 20); } ;
<verb3>         = dropped                               { return CH(1, 20); } ;
<verb3>         = bought                                { return CH(1, 20); } ;
<verb3>         = "heard about"                         { return CH(1, 20); } ;
<verb3>         = considered                            { return CH(1, 20); } ;
<verb3>         = "interacted with"                     { return CH(1, 20); } ;
<verb3>         = painted                               { return CH(1, 20); } ;
<verb3>         = <verb3>                               ;

# verb4 is agent-agent stuff.
<s>             = <agent> <verb4> <agent>               { return CH(1, 20); } ;

<verb4>         = hated                                 { return CH(1, 20); } ;
<verb4>         = killed                                { return CH(1, 20); } ;
<verb4>         = loved                                 { return CH(1, 20); } ;
<verb4>         = "disagreed with"                      { return CH(1, 20); } ;
<verb4>         = imitated                              { return CH(1, 20); } ;
<verb4>         = "talked to"                           { return CH(1, 20); } ;
<verb4>         = <verb4>                               ;

# verb5 is agent-intangible stuff. (I don't know about this...)
<s>             = <agent> <verb5> <intang-obj>          { return CH(1, 20); } ;

<verb5>         = felt                                  { return CH(1, 20); } ;
<verb5>         = enjoyed                               { return CH(1, 20); } ;
<verb5>         = <verb5>                               ;

# Now for some more things -- intentional statements, (some of these
# may turn out to be ungrammatical, for instance by not using the subjunctive
# mode)...

<s>             = <agent> <int-verb> <s>                { return CH(1, 20); } ;

<int-verb>      = "desired that"                        { return CH(1, 20); } ;
<int-verb>      = "believed that"                       { return CH(1, 20); } ;
<int-verb>      = "hoped that"                          { return CH(1, 20); } ;
<int-verb>      = "thought that"                        { return CH(1, 20); } ;
<int-verb>      = "wished that"                         { return CH(1, 20); } ;
<int-verb>      = "feared that"                         { return CH(1, 20); } ;
<int-verb>      = "wondered whether"                    { return CH(1, 20); } ;
<int-verb>      = "was worried that"                    { return CH(1, 20); } ;
<int-verb>      = "figured that"                        { return CH(1, 20); } ;
<int-verb>      = "predicted that"                      { return CH(1, 20); } ;
<int-verb>      = "was ashamed that"                    { return CH(1, 20); } ;
<int-verb>      = <int-verb>                            ;

<s>             = <s>                                   ;

<adv>           = ""                                    { return CH(4, 5); } ;
<adv>           = <Adv>                                 ;

<in-rel-to>     = <prep>                                { return CH(1, 4); } ;
<in-rel-to>     = "similar to"                          { return CH(1, 20); } ;
<in-rel-to>     = "in contact with"                     { return CH(1, 20); } ;
<in-rel-to>     = "not at all like"                     { return CH(1, 20); } ;
<in-rel-to>     = "reminicent of"                       { return CH(1, 20); } ;
<in-rel-to>     = "a part of"                           { return CH(1, 20); } ;
<in-rel-to>     = "exactly like"                        { return CH(1, 20); } ;
<in-rel-to>     = <in-rel-to>                           ;


# == NOUNS ==
# Here are the noun things -- there are agents, inanimate objects, and
# intangible objects (like concepts). Ignore pronouns for now.
# Intangible things don't have determiners, and don't have "tangible"
# adjectives attatched to them.

<thing>         = <agent>                               { return CH(1, 2); } ;
<thing>         = <inan-obj>                            ;

<agent>         = <agent1>                              ;

<agent1>        = <name-p>                              { return CH(1, 3); } ;
<agent1>        = <Det> <agent-adj> <Agent>             ;

<inan-obj>      = <A-Det> <thing-adj> <Inan-obj>        ;

<intang-obj>    = <intang-adj> <Intang-obj>             ;

<name-p>        = <Name>                                ;

<prep>          = "along with"                          { return CH(1, 10); } ;
<prep>          = "on top of"                           { return CH(1, 10); } ;
<prep>          = "next to"                             { return CH(1, 10); } ;
<prep>          = near                                  { return CH(1, 10); } ;
<prep>          = like                                  { return CH(1, 10); } ;
<prep>          = "apart from"                          { return CH(1, 10); } ;
<prep>          = "in addition to"                      { return CH(1, 10); } ;
<prep>          = <prep>                                ;

# == ADJECTIVES == 
# Intangible adjectives -- good, bad, etc. Tangible adjectives -- red, cold,
# etc. Agent agectives -- mean, selfish, etc. Agents can have any one, things
# can have tangible and intangible, but intangibles can have only intangibles.

<intang-adj>    = ""                                    { return CH(4, 5); } ;
<intang-adj>    = <Intang-adj> <intang-adj>             ;

<agent-adj>     = ""                                    { return CH(4, 5); } ;
<agent-adj>     = <adj1> <agent-adj>                    ;

<thing-adj>     = ""                                    { return CH(4, 5); } ;
<thing-adj>     = <adj2> <thing-adj>                    ;

<adj1>          = <Intang-adj>                          { return CH(1, 3); } ;
<adj1>          = <Agent-adj>                           { return CH(1, 3); } ;
<adj1>          = <Tang-adj>                            ;

<adj2>          = <Intang-adj>                          { return CH(1, 2); } ;
<adj2>          = <Tang-adj>                            ;

# Some generic words.

<Conj>          = but                                   { return CH(1, 20); } ;
<Conj>          = and                                   { return CH(1, 20); } ;
<Conj>          = or                                    { return CH(1, 20); } ;
<Conj>          = so                                    { return CH(1, 20); } ;
<Conj>          = however                               { return CH(1, 20); } ;
<Conj>          = nevertheless                          { return CH(1, 20); } ;
<Conj>          = therefore                             { return CH(1, 20); } ;
<Conj>          = <Conj>                                ;

# P-Det is a posession determiner -- can't be used with an agent.

<A-Det>         = <Det>                                 { return CH(1, 2); } ;
<A-Det>         = <P-Det>                               ;

<Det>           = a                                     { return CH(1, 10); } ;
<Det>           = the                                   { return CH(1, 7); } ;
<Det>           = that                                  { return CH(1, 15); } ;
<Det>           = "some kind of"                        { return CH(1, 20); } ;        
<Det>           = this                                  { return CH(1, 15); } ;
<Det>           = some                                  { return CH(1, 20); } ;
<Det>           = <Det>                                 ;

<P-Det>         = my                                    { return CH(1, 20); } ;
<P-Det>         = your                                  { return CH(1, 20); } ;
# The # mark here ---------v means don't put a space in between...
<P-Det>         = <agent1> "#'s"                        { return CH(1, 20); } ;
<P-Det>         = his                                   { return CH(1, 20); } ;
<P-Det>         = her                                   { return CH(1, 20); } ;
<P-Det>         = their                                 { return CH(1, 20); } ;
<P-Det>         = <P-Det>                               ;

<Agent>         = person                                { return CH(1, 20); } ;
<Agent>         = dog                                   { return CH(1, 20); } ;
<Agent>         = cat                                   { return CH(1, 20); } ;
<Agent>         = duck                                  { return CH(1, 20); } ;
<Agent>         = sheriff                               { return CH(1, 20); } ;
<Agent>         = professor                             { return CH(1, 20); } ;
<Agent>         = student                               { return CH(1, 20); } ;
<Agent>         = "CS grad student"                     { return CH(1, 20); } ;
<Agent>         = "disk jockey"                         { return CH(1, 20); } ;
<Agent>         = hacker                                { return CH(1, 20); } ;
<Agent>         = horse                                 { return CH(1, 20); } ;
<Agent>         = pig                                   { return CH(1, 20); } ;
<Agent>         = dude                                  { return CH(1, 20); } ;
<Agent>         = communist                             { return CH(1, 20); } ;
<Agent>         = goose                                 { return CH(1, 20); } ;
<Agent>         = scumbag                               { return CH(1, 20); } ;
<Agent>         = "scuba diver"                         { return CH(1, 20); } ;
<Agent>         = "disembodied spirit"                  { return CH(1, 20); } ;
<Agent>         = guy                                   { return CH(1, 20); } ;
<Agent>         = Australian                            { return CH(1, 20); } ;
<Agent>         = aardvark                              { return CH(1, 20); } ;
<Agent>         = "space alien"                         { return CH(1, 20); } ;
<Agent>         = <Agent>                               ;

<Inan-obj>      = house                                 { return CH(1, 20); } ;
<Inan-obj>      = fruit                                 { return CH(1, 20); } ;
<Inan-obj>      = slime-mold                            { return CH(1, 20); } ;
<Inan-obj>      = "lisp manual"                         { return CH(1, 20); } ;
<Inan-obj>      = rock                                  { return CH(1, 20); } ;
<Inan-obj>      = terminal                              { return CH(1, 20); } ;
<Inan-obj>      = textbook                              { return CH(1, 20); } ;
<Inan-obj>      = pen                                   { return CH(1, 20); } ;
<Inan-obj>      = box                                   { return CH(1, 20); } ;
<Inan-obj>      = steak                                 { return CH(1, 20); } ;
<Inan-obj>      = vax                                   { return CH(1, 20); } ;
<Inan-obj>      = "salad fork"                          { return CH(1, 20); } ;
<Inan-obj>      = thingamajig                           { return CH(1, 20); } ;
<Inan-obj>      = doorknob                              { return CH(1, 20); } ;
<Inan-obj>      = axe                                   { return CH(1, 20); } ;
<Inan-obj>      = "357 magnum"                          { return CH(1, 20); } ;
<Inan-obj>      = adm3a                                 { return CH(1, 20); } ;
<Inan-obj>      = saxaphone                             { return CH(1, 20); } ;
<Inan-obj>      = pineapple                             { return CH(1, 20); } ;
<Inan-obj>      = keyboard                              { return CH(1, 20); } ;
<Inan-obj>      = "baked potato"                        { return CH(1, 20); } ;
<Inan-obj>      = "carpet tack"                         { return CH(1, 20); } ;
<Inan-obj>      = "bottle of bee"                       { return CH(1, 20); } ;
<Inan-obj>      = coathanger                            { return CH(1, 20); } ;
<Inan-obj>      = "bayobab tree"                        { return CH(1, 20); } ;
<Inan-obj>      = <Inan-obj>                            ;

# These are all mental conditions.

<Intang-obj>    = fear                                  { return CH(1, 20); } ;
<Intang-obj>    = loathing                              { return CH(1, 20); } ;
<Intang-obj>    = sympathy                              { return CH(1, 20); } ;
<Intang-obj>    = hope                                  { return CH(1, 20); } ;
<Intang-obj>    = disgust                               { return CH(1, 20); } ;
<Intang-obj>    = envy                                  { return CH(1, 20); } ;
<Intang-obj>    = distaste                              { return CH(1, 20); } ;
<Intang-obj>    = excitement                            { return CH(1, 20); } ;
<Intang-obj>    = <Intang-obj>                          ;

<Name>          = "Generic Joe"                         { return CH(1, 20); } ;
<Name>          = John                                  { return CH(1, 20); } ;
<Name>          = Mary                                  { return CH(1, 20); } ;
<Name>          = "Ronald Reagan"                       { return CH(1, 20); } ;
<Name>          = "Fritz Mondale"                       { return CH(1, 20); } ;
<Name>          = "Marvin Minsky"                       { return CH(1, 20); } ;
<Name>          = "Howard the Duck"                     { return CH(1, 20); } ;
<Name>          = "Doug Cooper"                         { return CH(1, 20); } ;
<Name>          = Chris                                 { return CH(1, 20); } ;
<Name>          = Batman                                { return CH(1, 20); } ;
<Name>          = "Wyatt Earp"                          { return CH(1, 20); } ;
<Name>          = "Richard Nixon"                       { return CH(1, 20); } ;
<Name>          = "The Spanish Inquisition"             { return CH(1, 20); } ;
<Name>          = <Name>                                ;

<Intang-adj>    = lousy                                 { return CH(1, 20); } ;
<Intang-adj>    = undesirable                           { return CH(1, 20); } ;
<Intang-adj>    = bad                                   { return CH(1, 20); } ;
<Intang-adj>    = strange                               { return CH(1, 20); } ;
<Intang-adj>    = unexpected                            { return CH(1, 20); } ;
<Intang-adj>    = fascinating                           { return CH(1, 20); } ;
<Intang-adj>    = useful                                { return CH(1, 20); } ;
<Intang-adj>    = appropriate                           { return CH(1, 20); } ;
<Intang-adj>    = nice                                  { return CH(1, 20); } ;
<Intang-adj>    = incredible                            { return CH(1, 20); } ;
<Intang-adj>    = bizarre                               { return CH(1, 20); } ;
<Intang-adj>    = awful                                 { return CH(1, 20); } ;
<Intang-adj>    = unnatural                             { return CH(1, 20); } ;
<Intang-adj>    = "out of place"                        { return CH(1, 20); } ;
<Intang-adj>    = terrible                              { return CH(1, 20); } ;
<Intang-adj>    = <Intang-adj>                          ;

<Tang-adj>      = red                                   { return CH(1, 20); } ;
<Tang-adj>      = green                                 { return CH(1, 20); } ;
<Tang-adj>      = big                                   { return CH(1, 20); } ;
<Tang-adj>      = hot                                   { return CH(1, 20); } ;
<Tang-adj>      = heavy                                 { return CH(1, 20); } ;
<Tang-adj>      = fast                                  { return CH(1, 20); } ;
<Tang-adj>      = slow                                  { return CH(1, 20); } ;
<Tang-adj>      = huge                                  { return CH(1, 20); } ;
<Tang-adj>      = lumpy                                 { return CH(1, 20); } ;
<Tang-adj>      = <Agent> "#-like"                      { return CH(1, 20); } ;
<Tang-adj>      = <Inan-obj> "#-like"                   { return CH(1, 20); } ;
<Tang-adj>      = shabby                                { return CH(1, 20); } ;
<Tang-adj>      = <Tang-adj>                            ;

<Agent-adj>     = benevolent                            { return CH(1, 20); } ;
<Agent-adj>     = nasty                                 { return CH(1, 20); } ;
<Agent-adj>     = misanthropic                          { return CH(1, 20); } ;
<Agent-adj>     = conceited                             { return CH(1, 20); } ;
<Agent-adj>     = arrogant                              { return CH(1, 20); } ;
<Agent-adj>     = misguided                             { return CH(1, 20); } ;
<Agent-adj>     = nervous                               { return CH(1, 20); } ;
<Agent-adj>     = clever                                { return CH(1, 20); } ;
<Agent-adj>     = stupid                                { return CH(1, 20); } ;
<Agent-adj>     = <Agent-adj>                           ;

<Adv>           = quickly                               { return CH(1, 20); } ;
<Adv>           = badly                                 { return CH(1, 20); } ;
<Adv>           = slowly                                { return CH(1, 20); } ;
<Adv>           = stupidly                              { return CH(1, 20); } ;
<Adv>           = selfishly                             { return CH(1, 20); } ;
<Adv>           = properly                              { return CH(1, 20); } ;
<Adv>           = <Adv>                                 ;

<spunct>        = "."                                   ;

# Now, just for the heck of it, some random things...

<rnd>           = "what a" <Inan-obj> "!"               { return CH(1, 20); } ;
<rnd>           = "oh no, it's" <thing> "!"             { return CH(1, 20); } ;
<rnd>           = "NOBODY expects" <thing> "!"          { return CH(1, 20); } ;
<rnd>           = "look at" <thing> "!"                 { return CH(1, 20); } ;
<rnd>           = gosh!                                 { return CH(1, 20); } ;
<rnd>           = yeah, <s> .                           { return CH(1, 10); } ;
<rnd>           = "wouldn't ya know, " <s> "!"          { return CH(1, 20); } ;
<rnd>           = "well, shiver me timbers!"            { return CH(1, 20); } ;
<rnd>           = "lemme tell ya -" <s> "!"             { return CH(1, 20); } ;
<rnd>           = "why, you" <Inan-obj> "!"             { return CH(1, 20); } ;
<rnd>           = "look at me when I'm talking to you!" { return CH(1, 20); } ;
<rnd>           = <thing> ... uh...                     { return CH(1, 10); } ;
<rnd>           = uh...                                 { return CH(1, 20); } ;
<rnd>           = "hic! (excuse me...)"                 { return CH(1, 20); } ;
<rnd>           = "you know," <s> .                     { return CH(1, 20); } ;
<rnd>           = <agent> "said that" <s> .             { return CH(1, 5); } ;
<rnd>           = <rnd>                         ;

%%

