%{
/*
    Date: Fri, 25 Mar 94 10:16:48 PST
    From: ckleinja@Novell.COM (Connie Kleinjans)
    Subject: HUMOR: Shakespearean insults

    CREATE YOUR OWN SHAKESPEAREAN INSULTS  by Jerry Maguire, who teaches
    English at Center Grove High School in Greenwood, Indiana.

    Combine one word from each of the three columns below, prefaced with "Thou":

    Column 1         Column 2             Column 3

    artless          base-court           apple-john
    bawdy            bat-fowling          baggage
    beslubbering     beef-witted          barnacle
    bootless         beetle-headed        bladder
    churlish         boil-brained         boar-pig
    cockered         clapper-clawed       bugbear
    clouted          clay-brained         bum-bailey
    craven           common-kissing       canker-blossom
    currish          crook-pated          clack-dish
    dankish          dismal-dreaming      clotpole
    dissembling      dizzy-eyed           coxcomb
    droning          doghearted           codpiece
    errant           dread-bolted         death-token
    fawning          earth-vexing         dewberry
    fobbing          elf-skinned          flap-dragon
    froward          fat-kidneyed         flax-wench
    frothy           fen-sucked           flirt-gill
    gleeking         flap-mouthed         foot-licker
    goatish          fly-bitten           fustilarian
    gorbellied       folly-fallen         giglet
    impertinent      fool-born            gudgeon
    infectious       full-gorged          haggard
    jarring          guts-griping         harpy
    loggerheaded     half-faced           hedge-pig
    lumpish          hasty-witted         horn-beast
    mammering        hedge-born           hugger-mugger
    mangled          hell-hated           jolthead
    mewling          idle-headed          lewdster
    paunchy          ill-breeding         lout
    pribbling        ill-nurtured         maggot-pie
    puking           knotty-pated         malt-worm
    puny             milk-livered         mammet
    quailing         motley-minded        measle
    rank             onion-eyed           minnow
    reeky            plume-plucked        miscreant
    roguish          pottle-deep          moldwarp
    ruttish          pox-marked           mumble-news
    saucy            reeling-ripe         nut-hook
    spleeny          rough-hewn           pigeon-egg
    spongy           rude-growing         pignut
    surly            rump-fed             puttock
    tottering        shard-borne          pumpion
    unmuzzled        sheep-biting         ratsbane
    vain             spur-galled          scut
    venomed          swag-bellied         skainsmate
    villainous       tardy-gaited         strumpet
    warped           tickle-brained       varlot
    wayward          toad-spotted         vassal
    weedy            unchin-snouted       whey-face
    yeasty           weather-bitten       wagtail
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "runtime.h"

int rnum()
{
    return rand();
}

int choose(int n, int o)
{
    return rnum() % o < n ? 1 : 0;
}

#define CH(n_, o_) return choose((n_), (o_))

const char *column1[] = {
    "artless",
    "bawdy",
    "beslubbering",
    "bootless",
    "churlish",
    "cockered",
    "clouted",
    "craven",
    "currish",
    "dankish",
    "dissembling",
    "droning",
    "errant",
    "fawning",
    "fobbing",
    "froward",
    "frothy",
    "gleeking",
    "goatish",
    "gorbellied",
    "impertinent",
    "infectious",
    "jarring",
    "loggerheaded",
    "lumpish",
    "mammering",
    "mangled",
    "mewling",
    "paunchy",
    "pribbling",
    "puking",
    "puny",
    "quailing",
    "rank",
    "reeky",
    "roguish",
    "ruttish",
    "saucy",
    "spleeny",
    "spongy",
    "surly",
    "tottering",
    "unmuzzled",
    "vain",
    "venomed",
    "villainous",
    "warped",
    "wayward",
    "weedy",
    "yeasty",
    NULL
} ;

const char *column2[] = {
    "base-court",
    "bat-fowling",
    "beef-witted",
    "beetle-headed",
    "boil-brained",
    "clapper-clawed",
    "clay-brained",
    "common-kissing",
    "crook-pated",
    "dismal-dreaming",
    "dizzy-eyed",
    "doghearted",
    "dread-bolted",
    "earth-vexing",
    "elf-skinned",
    "fat-kidneyed",
    "fen-sucked",
    "flap-mouthed",
    "fly-bitten",
    "folly-fallen",
    "fool-born",
    "full-gorged",
    "guts-griping",
    "half-faced",
    "hasty-witted",
    "hedge-born",
    "hell-hated",
    "idle-headed",
    "ill-breeding",
    "ill-nurtured",
    "knotty-pated",
    "milk-livered",
    "motley-minded",
    "onion-eyed",
    "plume-plucked",
    "pottle-deep",
    "pox-marked",
    "reeling-ripe",
    "rough-hewn",
    "rude-growing",
    "rump-fed",
    "shard-borne",
    "sheep-biting",
    "spur-galled",
    "swag-bellied",
    "tardy-gaited",
    "tickle-brained",
    "toad-spotted",
    "unchin-snouted",
    "weather-bitten",
    NULL
} ;

const char *column3[] = {
    "apple-john",
    "baggage",
    "barnacle",
    "bladder",
    "boar-pig",
    "bugbear",
    "bum-bailey",
    "canker-blossom",
    "clack-dish",
    "clotpole",
    "coxcomb",
    "codpiece",
    "death-token",
    "dewberry",
    "flap-dragon",
    "flax-wench",
    "flirt-gill",
    "foot-licker",
    "fustilarian",
    "giglet",
    "gudgeon",
    "haggard",
    "harpy",
    "hedge-pig",
    "horn-beast",
    "hugger-mugger",
    "jolthead",
    "lewdster",
    "lout",
    "maggot-pie",
    "malt-worm",
    "mammet",
    "measle",
    "minnow",
    "miscreant",
    "moldwarp",
    "mumble-news",
    "nut-hook",
    "pigeon-egg",
    "pignut",
    "puttock",
    "pumpion",
    "ratsbane",
    "scut",
    "skainsmate",
    "strumpet",
    "varlot",
    "vassal",
    "whey-face",
    "wagtail",
    NULL
} ;

const char *lastchoice = NULL;

int getword(int type)
{
        const char **wds;
        int i = 0, j = 0, k;
        int alliterate = lastchoice ? (rand() % 4) : 0;

        switch (type) {
                case 1: wds = column1; break;
                case 2: wds = column2; break;
                case 3: wds = column3; break;
                default: fprintf(stderr, "Bad thing %d\n", type);
        }

        /* See how many words there are that we can use. */
        for (k = 0; wds[k]; k++) {
                if (alliterate && (*wds[k] == *lastchoice))
                        j++;
        }
        i = k;
        if (j == 0) {
hoho:
                i = rnum() % i;
                lastchoice = wds[i];
                g_computed = wds[i];
                return 1;
        } else {
                j = rnum() % j;
                for (k = 0; ; k++)
                        if (*wds[k] == (isupper(*lastchoice) ?
                                        tolower(*lastchoice) : *lastchoice)) {
                                if (wds[k] == lastchoice)
                                        goto hoho;
                                if (j == 0) {
                                        lastchoice = wds[k];
                                        g_computed = wds[k];
                                        return 1;
                                } else
                                        j--;
                        }
        }
}

/* Word types. */

%}

%%

<start>         = <invective> ;

<invective>     = Thou <der-term> ;

<der-term>      = <word3> <ep> { CH(1,3); } ;
<der-term>      = <word2> <word3> <ep> { CH(1,3); } ;
<der-term>      = <word1> <word2> <word3> <ep> { CH(1,3); } ;

<word1>         = { return (getword(1)); } ;
<word2>         = { return (getword(2)); } ;
<word3>         = { return (getword(3)); } ;

<ep>            = ! { lastchoice = NULL; return (1); } ;
