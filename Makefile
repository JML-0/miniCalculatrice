#NOM : <LEVACHER Jimmy>
#NUMERO : <18901505>
#EMAIL : <jimmygam@icloud.com>
# Auteur Far`es Belhadj amsi@ai.univ-paris8.fr
# Date le 02/10/2013
# Makefile g´en´erique

# d´efinition des commandes utilis´ees
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# d´eclaration des options pour gcc
PG_FLAGS =
CFLAGS = -Wall -O3 $(PG_FLAGS)
CPPFLAGS = -I.
LDFLAGS = $(PG_FLAGS)
# d´efinition des fichiers et dossiers
PROG = miniCalculatrice
PACKAGE = miniCalculatrice
VERSION = 1.0
distdir = $(PACKAGE)-$(VERSION)
HEADERS = pile.h ratio.h
SOURCES = miniCalculatrice.c pile.c ratio.c
OBJS = $(SOURCES:.c=.o)
DOXYFILE = documentation/Doxyfile
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(DOXYFILE)

all: $(PROG)

$(PROG): $(OBJS)
		$(CC) $^ $(LDFLAGS) -o $(PROG)

%.o: %.c
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

doc: $(DOXYFILE)
		cd documentation && doxygen && cd ..

dist: distdir
		$(CHMOD) -R a+r $(distdir)
		$(TAR) czvf $(distdir).tgz $(distdir)
		$(RM) -r $(distdir)
distdir: $(DISTFILES)
		$(RM) -r $(distdir)
		$(MKDIR) $(distdir)
		$(CHMOD) 777 $(distdir)
		$(CP) $(DISTFILES) $(distdir)
clean:
		@$(RM) $(PROG) $(OBJS) *~ $(distdir).tgz gmon.out documentation/*~ -r documentation/html