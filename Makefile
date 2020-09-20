BIN = MS.exe
SRC = src/program.c src/game.c src/player.c src/map.c src/level.c src/title.c

$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN) --debug -Wall -W -ansi -Werror -lSDL -lSDL_image -lSDL_ttf
	./$(BIN)
