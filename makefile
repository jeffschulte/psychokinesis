# Very basic makefile for the time being

WFLAGS=-Weverything -Wno-padded -Wno-documentation \
	-Wno-disabled-macro-expansion -Wno-sign-compare -Wno-sign-conversion
SDLFLAGS=`sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lliquidfun
CC=clang++

srcs=$(wildcard src/*.cpp)
heads=$(wildcard src/*.h)
objs=$(patsubst src%.cpp,build%.o,$(srcs))

default: bin/psycho

debug: CC += -g
debug: bin/psycho

build/%.o: src/%.cpp $(heads)
	$(CC) -c $< $(WFLAGS) $(SDLFLAGS) -o $@

bin/psycho: $(objs)
	$(CC) $(objs) $(WFLAGS) $(SDLFLAGS) $(LIBS) -o bin/psycho

$(objs): | objdir

objdir:
	mkdir -p build

bin/psycho: | bindir

bindir:
	mkdir -p bin

clean:
	rm -r bin
	rm -r build
