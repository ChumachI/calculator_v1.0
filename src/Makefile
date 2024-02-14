CC=gcc
CC_FLAGS=-Wall -Werror -Wextra
OS=$(shell uname)
LIB_NAME=s21_tests.a
TEST_FILES=$(shell find . -name "*test.c")
FILES=$(shell find . -name "*.c" ! -name "*test*")
GCOV_FLAGS=-coverage -fprofile-arcs -ftest-coverage
ifeq ($(OS), Linux)
  LCHECK_FLAGS = -lcheck -pthread -lsubunit -lrt -lm
  OPEN=xdg-open
else
  LCHECK_FLAGS = -lcheck
  OPEN=open
endif

all: install

install: uninstall clean
	mkdir build
	cd build/ && qmake ../frontend/frontend.pro && make
	./build/frontend
	

uninstall: clean

clean:
	rm -f *.o
	rm -f test
	rm -f s21_tests.a
	rm -f *info*
	rm -rf tmp
	rm -rf report
	rm -rf docs
	rm -rf build
	rm -rf html
	rm -rf latex

dvi:
	mkdir -p docs
	doxygen Doxyfile
	@mv html latex docs
	open docs/html/index.html

dist:
	mkdir -p dist
	cp -r * dist
	tar -czf calcus.tar.gz dist
	rm -rf dist

test: $(LIB_NAME)
	$(CC) $(CC_FLAGS) -c $(TEST_FILES) 
	$(CC) -o test *.o $(CC_FLAGS) $(LCHECK_FLAGS) $(LIB_NAME) -g

.PHONY: $(LIB_NAME)
$(LIB_NAME):
	$(CC) $(CC_FLAGS) -c $(FILES) -g
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

gcov_report:
	$(CC) $(CC_FLAGS) $(FILES) $(TEST_FILES) $(LCHECK_FLAGS) $(GCOV_FLAGS)  -o info
	./info
	lcov -t "info" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	$(OPEN) report/index.html

test_back:
	$(CC)  -c $(FILES) -g 
	$(CC) -o test *.o -lm

style:
	clang-format -i */*/*.c
	clang-format -i */*.cpp
