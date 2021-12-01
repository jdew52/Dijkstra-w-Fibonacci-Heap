CC=g++
CFLAGS=
DEPS=fibheap.h graph.h
SRC=main.cpp fibheap.cpp graph.cpp

%: %.cpp $(DEPS)  # Force recompilation with headers
	$(CC) -c -o $@ $< $(CFLAGS)

compile: clean main
	$(CC) -o main $(SRC) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf main
