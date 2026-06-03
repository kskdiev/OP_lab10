CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fPIC -std=c11
LDFLAGS = -shared
INC = -I./include

.PHONY: all clean shared app run syntax test py-test analyze sanitize docs docs-html docs-pdf

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

py-test: shared
	python3 python/test_rect.py

syntax:
	$(CC) -fsyntax-only $(CFLAGS) $(INC) src/*.c tests/*.c

analyze: build
	@mkdir -p reports
	$(CC) -fanalyzer $(CFLAGS) $(INC) -c src/rect.c > reports/analyzer_report.txt 2>&1 || true
	@echo "Статический анализ завершен. Отчет в reports/analyzer_report.txt"

sanitize: build
	@mkdir -p reports
	$(CC) $(CFLAGS) -fsanitize=address,undefined $(INC) src/rect.c tests/test_rect.c -o build/sanitize_test
	./build/sanitize_test > reports/sanitize_report.txt 2>&1
	@echo "Проверка санитайзерами завершена. Отчет в reports/sanitize_report.txt"

docs: docs-html docs-pdf

docs-html: Doxyfile
	doxygen Doxyfile

docs-pdf: docs-html
	$(MAKE) -C docs/latex pdf

clean:
	rm -rf build/ __pycache__/ docs/html/ docs/latex/ reports/*.txt *.so
