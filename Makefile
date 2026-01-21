CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -pg -no-pie -Werror

# ===== CLIENT (SDL) =====
CLIENT_TARGET = tradeAndReign
CLIENT_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer -lm

JEU_SRC     = $(shell find jeu -name "*.c")
SHARED_SRC  = $(shell find shared -name "*.c")

CLIENT_MAIN = jeu/main.c
CLIENT_SRC  = $(filter-out $(CLIENT_MAIN), $(JEU_SRC)) $(SHARED_SRC)

CLIENT_OBJ  = $(CLIENT_SRC:.c=.o)
CLIENT_MAIN_OBJ = $(CLIENT_MAIN:.c=.o)

# ===== SERVER (no SDL) =====
SERVER_TARGET = serveur

SERV_SRC = $(shell find serv -name "*.c")
SERVER_SRC = $(SERV_SRC) $(SHARED_SRC)
SERVER_LDFLAGS = -lm
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# ===== RULES =====
all: $(CLIENT_TARGET)

s: $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ)
	$(CC) $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ) -o $@ $(CLIENT_LDFLAGS)

$(SERVER_TARGET): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $@ $(SERVER_LDFLAGS)

# ----- Compilation générique -----
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ----- Clean -----
clean:
	rm -f $(CLIENT_OBJ) $(CLIENT_MAIN_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET)

re: fclean all

.PHONY: all clean fclean re j s

