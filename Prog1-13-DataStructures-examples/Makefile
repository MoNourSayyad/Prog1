CC = gcc
LINKER = gcc
CFLAGS = -std=gnu11 -Wall # -Werror -Wpointer-arith -Wfatal-errors
DEBUG = -g
PROG1LIBNAME = prog1
PROG1LIBDIR = ../prog1lib/lib

# disable default suffixes
.SUFFIXES:

# library
prog1lib:
	cd $(PROG1LIBDIR) && make

queue: queue.c 
	$(CC) $(CFLAGS) $(DEBUG) -o queue queue.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

vector: vector.c 
	$(CC) $(CFLAGS) $(DEBUG) -o vector vector.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

dyn_stack: dyn_stack.c 
	$(CC) $(CFLAGS) $(DEBUG) -o dyn_stack dyn_stack.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

dyn_queue: dyn_queue.c 
	$(CC) $(CFLAGS) $(DEBUG) -o dyn_queue dyn_queue.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

stack_tree: stack_tree.c integer_tree.c integer_list.c integer_tree.h integer_list.h
	$(CC) $(CFLAGS) $(DEBUG) -o stack_tree stack_tree.c integer_tree.c integer_list.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

queue_tree: queue_tree.c integer_tree.c integer_list.c integer_tree.h integer_list.h
	$(CC) $(CFLAGS) $(DEBUG) -o queue_tree queue_tree.c integer_tree.c integer_list.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

test_map: test_map.c map.c map.h
	$(CC) $(CFLAGS) $(DEBUG) -o test_map test_map.c map.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

test_set: test_set.c set.c set.h
	$(CC) $(CFLAGS) $(DEBUG) -o test_set test_set.c set.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

# delete intermediary files
.PHONY: clean		# do not treat "clean" as a file name
clean:				# special target to remove files: make clean
	rm -rf *.o *.dSYM
