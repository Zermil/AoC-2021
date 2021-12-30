@echo off

set CXX=g++
set FLAGS=-Wall -Wextra -Wshadow -pedantic -std=c++17

call %CXX% %FLAGS% -o main main.cpp
