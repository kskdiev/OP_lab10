.PHONY: all clean

all:
\t@mkdir -p build
\t@echo 'Сборка проекта...'

clean:
\trm -rf build/ __pycache__/ docs/html/ docs/latex/ reports/* *.so
