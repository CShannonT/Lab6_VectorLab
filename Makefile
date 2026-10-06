CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lm
SOURCES=management.c vectorMethods.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=VectorCalc

all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d