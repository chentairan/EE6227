# EE6227 Assignment 3

Name: Chen Tairan

Matriculation number: G2101544C

## Requirements

This code is written in C++. Thus if you want to build from source code, your system should have a C++ compilation environment. For convenience, I have also provided binary files that can be run under **macOS, Windows or Ubuntu**. Next I will describe the two methods of running from binary files and building from source code, respectively, under different operating systems.

### Build from source code

#### Windows

```bash
g++ main.cpp Genetic.cpp -o GA3 -std=c++11
./GA3
```

#### macOS / Ubuntu

**Option1: Using g++ compiler**

```bash
g++ main.cpp Genetic.cpp -o GA3 -std=c++11
./GA3
```

**Option2: Using cmake & make**

```bash
cd /path/to/this/code  # Change to your own code path
mkdir build
cd build
cmake ..
make
./GA3
```

### Run from binary files

In the `bin` directory there are my pre-compiled executable files, you can select the executable file that corresponds to your system to run.

#### Windows

Double-click the `.exe` file

#### macOS / Ubuntu

Open a terminal in the `bin` directory

```bash
./GA3_macOS	# if you use intel-based Mac
./GA3_linux	# if you use Ubuntu
```

**Note: These binaries are only valid for testing in my environment, if they fail to run, please build from source code !!!**