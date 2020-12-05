CC =g++
CFLAGS = -Wall -g -std=c++11
EXEC = test

build:
	$(CC) ./$(day)/solution.cpp -o ./$(day)/solution.out $(CFLAGS)

test: build
	./$(day)/solution.out < ./$(day)/input.txt

clean:
	rm ./$(day)/*.out
	rm -rf ./$(day)/*.dSYM