# **DATS** - **DAT**a **S**tructures

Compilation of various widely used data structures implemented in C for generic like data types.

***How can you achieve generics like C++ or Java in C ?***

**Dats** uses a combinason of *void pointer* and *function pointer* to abstract the data type it really uses.

***Is there some overhead using this trick ?***

Yes, the data pointed by void pointer must be heap allocated and often manipulated with pointer arithmetics. 

## Current Implemented Data Structures

This various data structures are designed with reading simplicity in mind first. 

**Data Structures:**

- [ ] Dynamic Array 
- [ ] Linked List   
- [ ] Binary Tree   

**Abstract Data Types:**

- [ ] Stack
- [ ] Queue 
- [ ] PriorityQueue
- [x] Hash Table
- [ ] Sparse Table
- [ ] DenseVec

## Examples

Coming soon...

## Building

Create the .a file:

> make lib

Get more info for the avaible commands: 

> make help