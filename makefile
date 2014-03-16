# Very basic makefile for the time being

WFLAGS=-Weverything -Wno-padded -Wno-documentation -Wno-sign-compare -Wno-sign-conversion
SDLFLAGS=-lSDL2_image `sdl2-config --cflags --libs`
CC=clang++ src/*.cpp

default: bin/psycho

debug: CC += -g
debug: bin/psycho

bin/psycho: src/*.cpp src/*.h
	$(CC) $(WFLAGS) $(SDLFLAGS) -o bin/psycho

clean:
	rm -r bin/*
