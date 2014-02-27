# Very basic makefile for the time being

bin/Capp: src/*.cpp src/CApp.h
	g++ src/*.cpp `sdl-config --cflags --libs` -o bin/CApp
