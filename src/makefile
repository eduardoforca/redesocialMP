IDIR =../include
CC=g++

CFLAGS=-I$(IDIR) -g -ftest-coverage -fprofile-arcs

ODIR=obj
LDIR =../lib

SLIBS = $(patsubst %,$(LDIR)/%,$(_SLIBS))
LIBS = -lncurses
LIBSMAIN = 
LIBSTEST = -pthread -lgtest

_DEPS = redeSocial.h grafo.h lista.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJC = redeSocial.o grafo.o lista.o
OBJC = $(patsubst %,$(ODIR)/%,$(_OBJC))

_OBJTEST = test_redesocial.o
OBJTEST = $(patsubst %,$(ODIR)/%,$(_OBJTEST))

_OBJMAIN = main.o
OBJMAIN = $(patsubst %,$(ODIR)/%,$(_OBJMAIN))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#-Wno-write-strings eh a flag para suprimir warnings a respeito de inicializacao de string em c++

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -Wno-write-strings 

test: $(OBJC) $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LIBSTEST)

main: $(OBJC) $(OBJMAIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LIBSMAIN)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
