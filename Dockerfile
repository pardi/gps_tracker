FROM ubuntu:22.04

RUN apt-get update && apt-get install cmake g++ libboost1.74-dev libboost-filesystem-dev libboost-iostreams-dev libgtest-dev gnuplot git -y

RUN git clone https://github.com/dstahlke/gnuplot-iostream.git deps/gnuplot-iostream