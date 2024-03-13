#!/usr/bin/bash

/usr/bin/g++ -c $1/main.cpp -o $1/main.o

/usr/bin/g++ $1/main.o -o $1/main -lsfml-graphics -lsfml-window -lsfml-system
