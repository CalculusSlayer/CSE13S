# Cite: TA Sloan
#
EXEC = sorting
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O2
LDFLAGS = -lm

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(OBJECTS)

format:
	clang-format -i -style=file *.[c,h]

