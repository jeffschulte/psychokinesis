# Very basic makefile for the time being

WFLAGS=-Weverything -Wno-padded -Wno-documentation \
	-Wno-disabled-macro-expansion -Wno-sign-compare -Wno-sign-conversion
SDLFLAGS=-lSDL2_image -lSDL2_mixer `sdl2-config --cflags --libs` -lliquidfun
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
	$(CC) $(objs) $(WFLAGS) $(SDLFLAGS) -o bin/psycho

$(objs): | objdir

objdir:
	mkdir -p build

bin/psycho: | bindir

bindir:
	mkdir -p bin

clean:
	rm -r bin
	rm -r build
