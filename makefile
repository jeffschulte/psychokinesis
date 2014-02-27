# Very basic makefile for the time being

bin/Capp: *.cpp Capp.h
	g++ src/*.cpp `sdl-config --cflags --libs` -o bin/Capp