CPPFLAGS = -Wall -g        
LDFLAGS = -lncurses         
SRC = ncurses_min.cpp      
EXEC = ncurses_min          

all:
	clang++ $(CPPFLAGS) $(LDFLAGS) $(SRC) -o $(EXEC)


clean:
	rm -f $(EXEC)


rebuild: clean all
