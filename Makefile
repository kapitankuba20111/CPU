build:
	rm -rf main
	g++ *.cpp -o main

run:
	./main

brun: build run