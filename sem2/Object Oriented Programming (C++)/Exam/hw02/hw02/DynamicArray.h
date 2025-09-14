#pragma once
#include "Product.h"
typedef Product* TElem;

typedef struct {
	TElem* elems;
	int size, capacity;
} DynamicArray;


DynamicArray* createDynamicArray(int capacity);
/*
* Creates a new dynamic array
* Input: capacity - integer
* Output: a pointer to a new dynamic array
*/
void append(DynamicArray* arr, TElem p);
/*
* Appends a new element to the dynamic array
* Input: arr - pointer to a dynamic array
* 	  p - pointer to an element
*/
void destroyArray(DynamicArray* arr);
/*
* Destroys a dynamic array and frees the memory
* Input: arr - pointer to a dynamic array
*/
int getSize(DynamicArray* arr);
/*
* Gets the size of the dynamic array
* Input: arr - pointer to a dynamic array
* Output: the size of the dynamic array
*/
int deleteElementFromArr(DynamicArray* arr, int pos);
/*
* Deletes an element from the dynamic array
* Input: arr - pointer to a dynamic array
* 	  pos - integer
* Output: 0 if the element was deleted successfully, 1 otherwise
*/
