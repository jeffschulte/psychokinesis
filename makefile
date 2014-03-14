# Very basic makefile for the time being

WFLAGS=-Weverything -Wno-padded -Wno-documentation -Wno-sign-compare -Wno-sign-conversion

bin/psycho: src/*.cpp src/*.h
	clang++ src/*.cpp $(WFLAGS) `sdl2-config --cflags --libs` -o bin/psycho
