#!/bin/bash

g++ -c main.cpp
g++ main.o -o sokoban -lsfml-graphics -lsfml-window -lsfml-system
