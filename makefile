# Very basic makefile for the time being

bin/psycho: src/*.cpp src/*.h
	clang++ src/*.cpp `sdl2-config --cflags --libs` -o bin/psycho
