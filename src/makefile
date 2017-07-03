IDIR =../include
CC=g++

CFLAGS=-I$(IDIR) -g -ftest-coverage -fprofile-arcs

ODIR=obj
LDIR =../lib

# #SLIBS indica bibliotecas estaticas na pasta lib, enquanto LIBS sao bibliotecas instaladas no sistema
# _SLIBS= liblista.a
SLIBS = $(patsubst %,$(LDIR)/%,$(_SLIBS))
LIBS = -pthread -lgtest

_DEPS = pessoa.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJC = pessoa.o
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
	$(CC) -o $@ $^ $(CFLAGS) $(SLIBS) $(LIBS)

main: $(OBJC) $(OBJMAIN)
	$(CC) -o $@ $^ $(CFLAGS) $(SLIBS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 