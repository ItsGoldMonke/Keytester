CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c17 -g
CPPFLAGS = $(shell pkg-config --cflags libcurl)
LDLIBS = $(shell pkg-config --libs libcurl)

TARGET = bin/keytester

SOURCES = src/main.c src/requests.c src/input.c
HEADERS = src/requests.h src/input.h

.PHONY = all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p bin
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)