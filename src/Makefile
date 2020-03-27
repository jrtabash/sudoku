CPP=clang++
CFLAGS=-std=c++17 -Wall -Wextra -Wformat -Werror
RM=rm -f
CP=cp
TARGET=sudoku

OBJS=\
	sudoku_board.o \
	sudoku_solver.o \
	sudoku_generator.o \
	sudoku_checker.o \
	sudoku_file.o \
	sudoku_arguments.o \
	sudoku_application.o \
	sudoku.o

ifeq ($(DEBUG), 0)
	CFLAGS += -DNDEBUG -O2
else
	CFLAGS += -DDEBUG
endif

$(TARGET): $(OBJS)
	$(CPP) $(LFLAGS) -o $(TARGET) $(OBJS)

sudoku.o: sudoku.cpp sudoku_board.h sudoku_solver.h
	$(CPP) $(CFLAGS) -c sudoku.cpp -o sudoku.o

sudoku_board.o: sudoku_board.cpp sudoku_board.h sudoku_alphabet.h
	$(CPP) $(CFLAGS) -c sudoku_board.cpp -o sudoku_board.o

sudoku_solver.o: sudoku_solver.cpp sudoku_solver.h sudoku_board.h sudoku_alphabet.h
	$(CPP) $(CFLAGS) -c sudoku_solver.cpp -o sudoku_solver.o

sudoku_generator.o: sudoku_generator.cpp sudoku_generator.h sudoku_board.h sudoku_alphabet.h
	$(CPP) $(CFLAGS) -c sudoku_generator.cpp -o sudoku_generator.o

sudoku_checker.o: sudoku_checker.cpp sudoku_checker.h sudoku_board.h sudoku_alphabet.h
	$(CPP) $(CFLAGS) -c sudoku_checker.cpp -o sudoku_checker.o

sudoku_file.o: sudoku_file.cpp sudoku_file.h sudoku_board.h
	$(CPP) $(CFLAGS) -c sudoku_file.cpp -o sudoku_file.o

sudoku_arguments.o: sudoku_arguments.cpp sudoku_arguments.h
	$(CPP) $(CFLAGS) -c sudoku_arguments.cpp -o sudoku_arguments.o

sudoku_application.o: sudoku_application.cpp sudoku_application.h sudoku_arguments.h
	$(CPP) $(CFLAGS) -c sudoku_application.cpp -o sudoku_application.o

clean: 
	$(RM) $(OBJS)
	$(RM) $(TARGET)

install:
	$(CP) $(TARGET) ~/bin/
