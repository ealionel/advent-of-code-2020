CC =g++
CFLAGS = -Wall -g -std=c++11
EXEC = test

build:
	$(CC) ./$(day)/solution.cpp -o ./$(day)/solution.out $(CFLAGS)

test: build
ifdef input
	./$(day)/solution.out < ./$(day)/$(input)
else
	./$(day)/solution.out < ./$(day)/input.txt
endif

clean:
	rm ./$(day)/*.out
	rm -rf ./$(day)/*.dSYM