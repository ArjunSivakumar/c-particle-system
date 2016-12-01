CC         = gcc
CFLAGS     = -c -Wall -ansi -pedantic
DEBUG      = -g
LIBS	   = -lglut -lGL -lGLU
SOURCES    = Sivakumar_particle.c Sivakumar_particles.c
OBJECTS    = $(SOURCES:.c=.o)
HEADER     = Sivakumar_particle.h
EXECUTABLE = Sivakumar_particle

all: $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS) $(DEBUG)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(EXECUTABLE)

