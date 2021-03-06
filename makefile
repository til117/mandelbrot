CC = gcc

# Read the config of SDL using the sdl-config tool
LIBS = $(shell sdl-config --libs)
CFLAGS = $(shell sdl-config --cflags)

MAIN = main
MAIN_OBJS = skeleton.c #mandelSDLzoom.c

$(MAIN): $(MAIN_OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN_OBJS) $(LIBS)

clean: 
	rm -f *.o $(MAIN)

debug:
	$(CC)  $(CFLAGS) -o $(MAIN) $(MAIN_OBJS) $(LIBS) -g

