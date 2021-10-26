# Minimal Oriented Bounding Box in 2D

This was an interview challenge in which an Oriented Bounding Box (OBB) had to
be found by using Principal Component Analysis (PCA). Nice one... :o)

### Build and Run

I use cmake for the build process.

```
$ git clone https://github.com/tylernewnoise/obb2D.git
$ cd obb2D
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
$ ./obb << ../input/input_example.v
```

### Input:
List of 2D vertices.

### Output:
Four 2D vertices representing a 2D oriented bounding box for input vertices.

### Examples:
Input:

x   |   y
:---: | :---:
3.7  |  1.7
4.1  |  3.8
4.7  |  2.9
5.2  |  2.8
6 4  |  4
6.3  |  3.6
9.7  |  6.3
10   |  4.9
11   |  3.6
12.5 |  6.4

Output:

x  | y
:---: | :---:
4.05| 0.82
2.94| 3.60
13.26| 4.50
12.15| 7.28

### Resources:
- https://www.youtube.com/watch?v=e50Bj7jn9IQ
- https://info.mathematik.uni-stuttgart.de/HM-Stroppel-Material/Eigenvectors/
- https://hewjunwei.wordpress.com/2013/01/26/obb-generation-via-principal-component-analysis/
- https://stackoverflow.com/a/56502134
