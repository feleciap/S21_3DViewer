CC = gcc -Wall -Werror -Wextra -std=c11
LIB_BACK = lib_3d_viewer.a
TESTS = tests/*.c
OS := $(shell uname)

ifeq ($(OS),Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
	OPEN_CMD = xdg-open
	QTFLAGS = CONFIG+=qtquickcompiler
else
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
	OPEN_CMD = open
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
endif

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: clean uninstall $(LIB_BACK) tests gcov_report install

$(LIB_BACK):
	$(CC) -c *.c
	ar -crs $(LIB_BACK) $(OBJ)

clang:
	-clang-format --style=Google -i *.c *.h

tests: clean $(LIB_BACK)
	$(CC) $(TESTS) *.c $(LIB_BACK) $(FLAGS) -o test
	./test

gcov_report: clean tests
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html
	rm -rf *.gcno *gcda *.gco

dvi:
	open ../README.MD

dist:
	mkdir 3D_Viewer_dist/
	mkdir 3D_Viewer_dist/src
	cp -R 3D_Viewer 3D_Viewer_dist/src
	cp -R tests 3D_Viewer_dist/src
	cp *.c *.h 3D_Viewer_dist/src
	cp -R 3d_models/cube.obj 3D_Viewer_dist/src
	cp -R Makefile 3D_Viewer_dist/src
	cp -R ../README.md 3D_Viewer_dist/src
	tar cvzf 3D_Viewer_dist.tgz 3D_Viewer_dist/
	rm -rf 3D_Viewer_dist

install: uninstall
	mkdir build
	cd build && qmake ../3D_Viewer/3D_Viewer.pro $(QTFLAGS) && /usr/bin/make -j8
	cd build && rm -rf *.o *.cpp *.h Makefile
	open ./build/

uninstall:
	rm -rf build

clean:
	rm -rf test $(LIB_BACK) *.o *.gcno *gcda *.gcov gcov report report.info