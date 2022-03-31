
# Disable the use of implicit build rules
.SUFFIXES:

# Use the clang compiler
CC = clang

# Set preprocessor flags
CPPFLAGS =

# Set compilation flags
#   -g          include debugging information
#   -Wall       report all warnings
#   -Werror     treat warnings as errors [note: compiler dependent]
#   -std=c11    use the 2011 version of the C standard
CFLAGS = -g -Wall -Werror -std=c11

# Set linker flags
LDFLAGS = 
#----------------------------------------------------------------------------
# build rules:
#
# Each rule takes the following form  (Note there MUST be a tab,
# as opposed to several spaces, preceeding each command.
#
# target_name:  dependency_list
#	command(s)

all: solve

# List program components, what they depend on, and how to compile or link each

solve:  solve.o queue.o path.o maze.o
	$(CC) $(LDFLAGS) -o $@ $^

solve.o:  solve.c queue.h path.h maze.h position.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

queue.o:  queue.c queue.h path.h 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

path.o:  path.c path.h position.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

maze.o:  maze.c maze.h position.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<


#----------------------------------------------------------------------------
# cleanup rules: To invoke this command, type "make clean".
# Use this target to clean up your directory, deleting (without warning) 
#   the built program, object files, old emacs source versions, and core dumps.

clean:
	rm -f solve *.o *~ core*



