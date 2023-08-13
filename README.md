# GPS tracker
This is a simple class that reads a "fake" GPS data file in .csv, stores the data into an object, and allows operations such as plotting, pulling statistics, etc.

## Requirements
```
sudo apt-get update
sudo apt-get install cmake g++ libboost1.74-dev libboost-filesystem-dev \
                     libboost-iostreams-dev libgtest-dev gnuplot -y
```

## Graphics
We use gnuplot for visualising the path. [here](http://stahlke.org/dan/gnuplot-iostream/) a tutorial on how to use it can be found.
