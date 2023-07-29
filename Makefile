SOURCES := $(shell find . -name "*.cpp")
HEADERS := $(shell find . -name "*.hpp")
HEADERDIRS := $(sort $(dir $(HEADERS)))
INCLUDEFLAGS := $(addprefix -I,$(HEADERDIRS))
LIBRARIES := -lSDL2 -lSDL2_image -lSDL2_ttf
FILE_OUT := crawl.out


build: clean
	g++ $(SOURCES) $(LIBRARIES)  -w $(INCLUDEFLAGS) -o $(FILE_OUT)
run: build
	./$(FILE_OUT)
clean: 
	rm -rf $(FILE_OUT)