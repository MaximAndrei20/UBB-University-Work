#pragma once
#include "Repository.h"
#include "Product.h"
#include "DynamicArray.h"

typedef struct {
    Repository* repo;
    DynamicArray** undoStack;
    int undoStackSize;
    int undoStackCapacity;
    DynamicArray** redoStack;
    int redoStackSize;
    int redoStackCapacity;
} Service;

Service* createService(Repository* repo);
/*
* Creates a new service
* Input: repo - pointer to a repository
* Output: a pointer to a new service
*/

void destroyService(Service* s);
/*
* Destroys a service and frees the memory
* Input: s - pointer to a service
* 
*/
int addProduct(Service* s, char* name, char* category, int quantity, char* expirationDate);
/*
* Adds a new product to the repository
* Input: s - pointer to a service
*        name - pointer to a string
* 	  category - pointer to a string
* 	  quantity - integer
* 	  expirationDate - pointer to a string
* Output: 0 if the product was added successfully, 1 otherwise
*/
int deleteProduct(Service* s, char* name, char* category);
/*
* Deletes a product from the repository
* Input: s - pointer to a service
* 	  name - pointer to a string
* 	  category - pointer to a string
* Output: 0 if the product was deleted successfully, 1 otherwise
*/
Product** getSortedProductsByString(Service* s, const char* str, int* outSize);
/*
* Returns an array of products sorted by quantity
* Input: s - pointer to a service
* 	  str - pointer to a string
* 	  outSize - pointer to an integer
* Output: an array of products
*/
Product** getProductsByCategoryAndExpiration(Service* s, const char* category, int days, int* outSize);
/*
*   Returns an array of products that have a certain expiration date
* Input: s - pointer to a service
* 	  category - pointer to a string
* 	  days - integer
* 	  outSize - pointer to an integer  
* Output: an array of products
*/
int updateProduct(Service* s, Product* p, char* newName, char* newCategory, int newQuantity, char* newExpirationDate);
/*
* Updates a product
* Input: s - pointer to a service
* 	  p - pointer to a product
* 	  newName - pointer to a string
* 	  newCategory - pointer to a string
* 	  newQuantity - integer
* 	  newExpirationDate - pointer to a string
* Output: 0 if the product was updated successfully, 1 otherwise
*/
int undo(Service* s);
/*
* Undoes the last operation
* Input: s - pointer to a service
* Output: 0 if the operation was successful, 1 otherwise
*/
int redo(Service* s);
/*
* Redoes the last operation
* Input: s - pointer to a service
* Output: 0 if the operation was successful, 1 otherwise
*/
