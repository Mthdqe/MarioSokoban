BIN = MS
SRC = program.c game.c player.c map.c level.c title.c

$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN) --debug -Wall -W -ansi -Werror -lSDL -lSDL_image -lSDL_ttf
	./$(BIN)
