CC = g++-11

all: queue stack

.PHONY: queue
queue: queue.cpp
	$(CC) -o queue -Ofast queue.cpp

.PHONY: stack
stack: stack.cpp
	$(CC) -o stack -Ofast stack.cpp