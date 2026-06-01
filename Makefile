CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fPIC -std=c11
LDFLAGS = -shared
INC = -I./include

.PHONY: all clean shared app run syntax test

all: shared app

build:
	mkdir -p build

shared: build build/librect.so

build/librect.so: src/rect.c
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $< -o $@

app: build build/demo_app

build/demo_app: src/demo.c build/librect.so
	$(CC) $(CFLAGS) $(INC) $< -L./build -lrect -Wl,-rpath,./build -o $@

run: app
	./build/demo_app

test: build build/test_rect
	./build/test_rect

build/test_rect: tests/test_rect.c build/librect.so
	$(CC) $(CFLAGS) $(INC) $< -L./build -lrect -Wl,-rpath,./build -o $@

syntax:
	$(CC) -fsyntax-only $(CFLAGS) $(INC) src/*.c tests/*.c

clean:
	rm -rf build/ __pycache__/ docs/html/ docs/latex/ reports/* *.so
