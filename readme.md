# Fantasy-FIRST

An idea to run a script that generates results for certain input teams. Now, here's the bad idea part of this. We're gonna try and use a C++ script as one of the implementations.

# Installation for C++
```bash
sudo apt install libcurl4-openssl-dev
sudo apt-get install make
```

## Libraries (C++)
[JSON for Modern C++](https://github.com/nlohmann/json)

## Input File Formatting
For the C++ program, we use input redirection when entering lineups. One example of a validly formatted file would be:
```
Name1
3
127
9898
2939
y
Name2
3
347
9839
393
q
```
The conventions of the file are as follows:
1. Type in the Name of the Person
2. Type in the number of teams in their lineup
3. Enter the team numbers
4. Enter 'y' if you want to keep looping OR 'q' to exit.

## C++ Execution
To execute the code for the makefile you have three possible commands:
```bash
make run
make run INPUT_FILE=someFile.input
make run INPUT_FILE=someFile.input COMPETITION_KEY=someComp
```
