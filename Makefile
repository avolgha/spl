CC     := clang
CFLAGS := -Wall -Wextra -Wshadow -pedantic
LFLAGS := -lm

SRCS   := $(wildcard src/*.c)
OBJS   := $(patsubst src/%.c,build/%.o,$(SRCS))
BIN    := spl

.PHONY: all test format clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: test.sh $(BIN)
	./test.sh

format:
	clang-format --verbose -i src/*.{c,h}

clean:
	$(RM) $(OBJS) $(BIN)

