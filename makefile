CC=gcc
CFLAGS=-Wall -ansi -I$(IDIR) -g -l$(BINDIR)

IDIR=./includes/
SRCDIR=./src/
BINDIR=./bin/

SOURCES = $(SRCDIR)*.c

all: contactList

contactList: $(BINDIR)contactList.o $(BINDIR)functions.o
	$(CC) $(BINDIR)contactList.o $(BINDIR)functions.o -o $(BINDIR)$@

$(BINDIR)contactList.o: $(SRCDIR)contactList.c
	$(CC) $(CFLAGS) -c $(SRCDIR)contactList.c -o $@

$(BINDIR)functions.o: $(SRCDIR)functions.c
	$(CC) $(CFLAGS) -c $(SRCDIR)functions.c -o $@

run: contactList
	./bin/contactList

clean: 
	rm ./bin/*.o bin/contactList

