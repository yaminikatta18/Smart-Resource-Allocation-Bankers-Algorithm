CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
TARGET = bankers
SOURCE = src/bankers.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

test: $(TARGET)
	bash tests/test_bankers.sh

clean:
	rm -f $(TARGET)

.PHONY: all test clean
