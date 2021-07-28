# **DATS** - **DAT**a **S**tructures

Compilation of various widely used data structures implemented in C for generic like data types.

***How can you achieve generics like C++ or Java in C ?***

**Dats** uses a combinason of *void pointer* and *function pointer* to abstract the data type it really uses.

***Is there some overhead using this trick ?***

Yes, the data pointed by void pointer must be heap allocated and often manipulated with pointer arithmetics. 

***Why is there C++ files if Dats is in pure C ?***

Dats uses **googletest** or **gtest.h** for unit testing. This testing framework uses .cpp files to write C and C++ test unit. So, we only have .cpp files for testing the rest is pure C. 

## Current Implemented Data Structures

This various data structures are designed with reading simplicity in mind first. 

**Data Structures:**

- [x] Dynamic Array 
- [x] Linked List
- [X] Binary Search Tree
- [x] Stack
- [X] Queue 
- [X] Hash Table
- [X] Bitset
- [X] DenseArray

- [ ] Hibitset
- [ ] PriorityQueue
- [ ] Generational Indexes

## Examples

Coming soon...

## Building

Create the .a file:

> make lib

Get more info for the avaible commands: 

> make help