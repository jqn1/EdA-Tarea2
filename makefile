# Detectar sistema operativo
UNAME_S := $(shell uname -s)

# Variables base
CC = gcc
CFLAGS = -Wall -O2
SRC = main.c modules/*.c
OUT = app

# Selección de compilador según sistema
ifeq ($(UNAME_S),Darwin)
    CC = clang
endif

# Compilación
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Ejecutar el programa en terminal
run: all
	./$(OUT)

# Limpiar archivos generados
clean:
	rm -f $(OUT)

# Compilación con depuración
debug:
	$(CC) $(CFLAGS) -g $(SRC) -o $(OUT)


