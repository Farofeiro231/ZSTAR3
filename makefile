IDIR = headers
SRC = source
ODIR = objects

CC = gcc
CFLAGS = -I$(IDIR)

#ODIR = obj
#LIBS = -lm

_DEPS = data.h driver.h comunication.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_C_DEPS = comunication.c driver.c
C_DEPS  = $(patsubst %, $(SRC)/%, $(_C_DEPS))

_OBJ = comunication.o driver.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	gcc -o $@ $(SRC)/main.c $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o

# $< usa o primeiro item na lista de dependencias do target
# $@ usa o nome que está do lado esquerdo do :
# # patsubst poe os nomes do terceiro argumento no segundo
