CC    := clang
CLAGS := -Wall -Wextra -Wshadow -pedantic

SRCS  := $(wildcard *.c)
OBJS  := $(SRCS:.c=.o)
BIN   := spl

.PHONY: all test clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BIN)
	./$(BIN) "1 1 +"

clean:
	$(RM) $(OBJS) $(BIN)
