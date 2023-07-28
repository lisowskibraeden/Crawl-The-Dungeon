build:
	g++ *.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -w -o crawl.out
run: build
	./crawl.out
clean: 
	rm -rf *.out