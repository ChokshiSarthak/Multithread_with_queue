CCFLAGS = g++ -Wall
LDFLAGS = -lpthread
SRC = main.cc thread.cc
OBJ = $(SRC:.cc=.o)

thread_example: $(OBJ)
	$(CCFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) thread_example




