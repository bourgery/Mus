CC = gcc
CFLAGS = -std=c99 -g -Wall
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf
SRC = src/main.c src/jeu.c src/affichage.c src/jeu_IA.c
OBJ = $(SRC:.c=.o)

all: mus

mus: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(SDLFLAGS)

%.o: %.c 
	@$(CC) $(CFLAGS) -o $@ -c $< 

play: 
	@./mus

clean: 
	@rm -f src/*~ src/*.o mus
