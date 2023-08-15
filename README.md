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

## Testing
We use `gtest` for doing the testing of the library.
