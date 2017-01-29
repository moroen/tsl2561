CC=gcc
CFLAGS=
INCLUDES= -I. -I./src -I/usr/include/python3.4
LIBS=-lwiringPi -lpython3.4m -lm
OBJDIR=obj
SRCDIR=src
DEPS = $(SRCDIR)/tsl2561.h

_OBJS = lux.o tsl2561.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c $(INCLUDES) -o $@ $< $(CFLAGS)


all: lux python

lux: $(OBJDIR)/lux.o $(OBJDIR)/tsl2561.o
	gcc -o lux $(OBJDIR)/lux.o $(OBJDIR)/tsl2561.o $(LIBS)

python: $(SRCDIR)/tsl2561_py_module.c $(OBJDIR)/tsl2561.o
	python3 setup.py build

clean:
	rm -rf *.o lux build/* obj/*
