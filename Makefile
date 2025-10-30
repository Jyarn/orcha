CC=gcc
OBJ=types.o
CFLAGS=-Wpedantic -Wextra -Wall -g
LFLAGS=
OUT=trisp

all: $(OUT)

run: test.o $(OBJ)
	$(CC) $(LFLAGS) $^ -o test
	./test

$(OUT): main.o $(OBJ)
	$(CC) $(LFLAGS) $^ -o $(OUT)

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm *.o
	rm $(OUT)
	rm test
