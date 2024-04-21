PILOT_NAME = droitAuBut

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -Wpedantic -g
LDLIBS = -lm

SANITIZE=off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize=address
endif

.PHONY: all clean distclean install try

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
DRIVERS_PATH = ../drivers

# Liste de tous les fichiers source .c dans le répertoire src
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Générer une liste des fichiers objets en remplaçant .c par .o dans le répertoire obj
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(PILOT_NAME)

install: $(DRIVERS_PATH)/$(PILOT_NAME)

try: install
	cd .. ; ./GrandPrix

$(PILOT_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(DRIVERS_PATH)/$(PILOT_NAME): $(PILOT_NAME)
	cp $(PILOT_NAME) $(DRIVERS_PATH)

# Règle de compilation pour les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $< $(LDLIBS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

distclean: clean
	rm -f $(PILOT_NAME)

clean:
	rm -f *~ $(PILOT_NAME)
	rm -rf $(OBJ_DIR)
