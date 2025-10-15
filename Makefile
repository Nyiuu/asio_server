CXXFLAGS=-std=c++20 -Wall -Wextra

all: echo_co_server

echo_co_server: echo_co_server.cpp
	clang++ $(CXXFLAGS) -o echo_co_server echo_co_server.cpp
