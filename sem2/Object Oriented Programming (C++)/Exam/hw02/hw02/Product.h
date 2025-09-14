#pragma once

typedef struct {
	char* name;
	char* category;
	int quantity;
	char* expirationDate;
} Product;


Product* createProduct(char* name, char* category, int quantity, char* expirationDate);
/*
* Creates a new product
* Input: name - pointer to a string
* 	  category - pointer to a string
* 	  quantity - integer
* 	  expirationDate - pointer to a string
* Output: a pointer to a new product
*/
void destroyProduct(Product* p);
/*
* Destroys a product and frees the memory
* Input: p - pointer to a product
*/
char* getName(Product* p);
/*
* Gets the name of a product
* Input: p - pointer to a product
* Output: the name of the product
*/
char* getCategory(Product* p);
/*
* Gets the category of a product
* Input: p - pointer to a product
* Output: the category of the product
*/
int getQuantity(Product* p);
/*
* Gets the quantity of a product
* Input: p - pointer to a product
* Output: the quantity of the product
*/
char* getExpirationDate(Product* p);
/*
* Gets the expiration date of a product
* Input: p - pointer to a product
* Output: the expiration date of the product
*/
void setName(Product* p, char* name);
/*
* Sets the name of a product
* Input: p - pointer to a product
* 	  name - pointer to a string
*/
void setCategory(Product* p, char* category);
/*
* Sets the category of a product
* Input: p - pointer to a product
* 	  category - pointer to a string
*/
void setQuantity(Product* p, int quantity);
/*
* Sets the quantity of a product
* Input: p - pointer to a product
* 	  quantity - integer
*/
void setExpirationDate(Product* p, char* expirationDate);
/*
* Sets the expiration date of a product
* Input: p - pointer to a product
* 	  expirationDate - pointer to a string
*/
