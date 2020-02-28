#Configuration
CC = g++
CFLAGS = -Wall -g
LFLAGS = -lcurl
TARGET = out

#Generate Source Files
CPLUS_SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h libs/*.hpp)
OBJECTS := $(patsubst src/%.cpp, bin/%.o, $(wildcard src/*.cpp))

#default target
all: build
	@echo "COMPLETED!"

#Link all built objects
build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LFLAGS)
	@echo "BUILD COMPLETED"

#Generate Object Files if they don't already exist.
bin/%.o: src/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(TARGET)

#Print the Files that Exist
which:
	@echo "FOUND SOURCES: $(CPLUS_SOURCES)"
	@echo "FOUND HEADERS: $(HEADERS)"
	@echo "FOUND OBJECTS: $(OBJECTS)"
