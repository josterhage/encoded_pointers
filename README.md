## Encoded Pointers
This is an experiment in creating a type-safe method of encoding small amounts of data into a pointer as part of an AVL Tree implementation.

### Building
Simply run `make` in the root directory of the source tree. It's written against C++23, so you'll probably need gcc version 11.x or later, or clang version 19+. The make file calls `g++`, but you can specify your own compiler by setting `CXX=`,
either with the make call or as an environmental variable.
