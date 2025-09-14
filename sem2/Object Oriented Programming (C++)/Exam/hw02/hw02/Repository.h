#pragma once
#include "DynamicArray.h"
typedef struct {
	DynamicArray* da;
}Repository;

Repository* createRepository();
/*
* Creates a new repository
* Output: a pointer to a new repository
*/
void destroyRepository(Repository* repo);
/*
* Destroys a repository and frees the memory
* Input: repo - pointer to a repository
*/
void addElement(Repository* repo, TElem* elem);
/*
* Adds a new element to the repository
* Input: repo - pointer to a repository
* 	  elem - pointer to an element
*/
int deleteElement(Repository* repo, char* name, char* category);
/*
* Deletes an element from the repository
* Input: repo - pointer to a repository
* 	  name - pointer to a string
* 	  category - pointer to a string
* Output: 0 if the element was deleted successfully, 1 otherwise
*/
int findElement(Repository* repo, char* name, char* category);
/*
* Finds an element in the repository
* Input: repo - pointer to a repository
* 	  name - pointer to a string
* 	  category - pointer to a string
* Output: the position of the element if it was found, -1 otherwise
*/
void setQuantityToPos(Repository* repo, int quantity, int pos);
/*
* Sets the quantity of an element at a given position
* Input: repo - pointer to a repository
* 	  quantity - integer
* 	  pos - integer
*/
int getQuantityOfPos(Repository* repo, int pos);
/*
* Gets the quantity of an element at a given position
* Input: repo - pointer to a repository
* 	  pos - integer
* Output: the quantity of the element at the given position
*/