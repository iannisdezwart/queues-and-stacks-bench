all: queue stack

.PHONY: queue
queue: queue.cpp
	$(CXX) -o queue -Ofast queue.cpp

.PHONY: stack
stack: stack.cpp
	$(CXX) -o stack -Ofast stack.cpp
