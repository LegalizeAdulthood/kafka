
# RCS Info: $Revision: 1.2 $ on $Date: 1995/09/02 07:58:48 $
#           $Source: /home/users/l/legalize/src/kafka/RCS/Makefile,v $
# Copyright (c) 1985 Wayne A. Christopher 
#	Permission is granted to do anything with this code except sell it
#	or remove this message.
#
# The makefile for everything.

CFILES = dstrans.c etc.c funwords.c init.c main.c \
	maketext.c output.c psubr.c stuff.c

KFILES = babble.k flame.k insult.k

HFILES = defs.h graph.h kafgraf.h

OFILES = dstrans.o init.o main.o psubr.o stuff.o \
	lex.yy.o y.tab.o

RUNOFILES = etc.o maketext.o output.o

# CC = cc
# YACC = yacc
# LEX = lex
CC = gcc
YACC = bison
LEX = flex

all: kafka insult babble flame buttplug

kafka: $(OFILES)
	$(CC) $(CFLAGS) -o kafka $(OFILES)

buttplug: kafka buttplug.k $(RUNOFILES) buttplug.spec.o buttplug.text.o
	$(CC) $(LFLAGS) $(CFLAGS) -o buttplug \
		$(RUNOFILES) buttplug.spec.o buttplug.text.o

buttplug.spec.c buttplug.text.c: buttplug.k
	./kafka buttplug.k
	mv kaf.spec.c buttplug.spec.c 
	mv kaf.text.c buttplug.text.c

bill: bill.k $(RUNOFILES)
	./kafka bill.k
	$(CC) $(CFLAGS) -c kaf.spec.c kaf.text.c
	$(CC) $(CFLAGS) -o bill $(RUNOFILES) kaf.spec.o kaf.text.o

insult: insult.k $(RUNOFILES)
	./kafka insult.k
	$(CC) $(CFLAGS) -c kaf.spec.c kaf.text.c
	$(CC) $(CFLAGS) -o insult $(RUNOFILES) kaf.spec.o kaf.text.o

babble: babble.k $(RUNOFILES)
	./kafka babble.k
	$(CC) $(CFLAGS) -c kaf.spec.c kaf.text.c
	$(CC) $(CFLAGS) -o babble $(RUNOFILES) kaf.spec.o kaf.text.o

flame:	flame.k $(RUNOFILES)
	./kafka flame.k
	$(CC) $(CFLAGS) -c kaf.spec.c kaf.text.c
	$(CC) $(CFLAGS) -o flame $(RUNOFILES) kaf.spec.o kaf.text.o

lex.yy.c: lexical.l y.tab.h
	$(LEX) lexical.l
	egrep -v '^# define (input|unput)' < lex.yy.c > ltmp
	mv ltmp lex.yy.c

y.tab.c y.tab.h: parse.y
	$(YACC) -d parse.y

