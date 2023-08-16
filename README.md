# GPS tracker
This is a simple class that reads a "fake" GPS data file in .csv, stores the data into an object, and allows operations such as plotting, pulling statistics, etc.

## Requirements
```
sudo apt-get update
sudo apt-get install cmake g++ libboost1.74-dev libboost-filesystem-dev \
                     libboost-iostreams-dev libgtest-dev gnuplot -y
```

## Dockerfile
We provide a `Dockerfile` with the environment for compiling and testing the library.

## Graphics
Plotting and visualisation in C++ is a finicky operation, therefore, we decided to use one of the most common library for visualisation: `gnuplot`. [Here](http://stahlke.org/dan/gnuplot-iostream/) is a tutorial on how to use it for further modifications.

To download the library, you can run:
```
git clone https://github.com/dstahlke/gnuplot-iostream.git /app/deps/gnuplot-iostream
```

The folder where to download the library is set up to work in the docker image. 

If you want to run this locally, please change the folder to the one of your choosing and update the `CMakeFile.txt` accordingly.

## Installation
```
mkdir build && cd build
cmake ..
make
```

## Testing
We use `gtest` for doing the testing of the library.

```
ctest
```
add `verbose` option for more details
