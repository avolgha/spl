CC     := clang
CFLAGS := -Wall -Wextra -Wshadow -pedantic
LFLAGS := -lm

SRCS   := $(wildcard *.c)
OBJS   := $(SRCS:.c=.o)
BIN    := spl

.PHONY: all test clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BIN)
	./$(BIN) "1 1 +"

format:
	clang-format --verbose -i *.{c,h}

clean:
	$(RM) $(OBJS) $(BIN)
