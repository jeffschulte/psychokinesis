# Very basic makefile for the time being

WFLAGS=-Weverything -Wno-padded -Wno-documentation \
	-Wno-disabled-macro-expansion -Wno-sign-compare -Wno-sign-conversion
SDLFLAGS=-lSDL2_image -lSDL_mixer `sdl2-config --cflags --libs`
CC=clang++

default: bin/psycho

debug: CC += -g
debug: bin/psycho

bin/psycho: src/*.cpp src/*.h
	$(CC) src/*.cpp $(WFLAGS) $(SDLFLAGS) -o bin/psycho

clean:
	rm -r bin/*
