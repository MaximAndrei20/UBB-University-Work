#include "Product.h"
#include <stdlib.h>
#include <string.h>

Product* createProduct(char* name, char* category, int quantity, char* expirationDate)
{
	Product* p = (Product*)malloc(sizeof(Product));
	if (p == NULL)
		return NULL;

	p->name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	if (p->name == NULL)
		return NULL;
	strcpy(p->name, name);

	p->category = (char*)malloc(sizeof(char)*(strlen(category) + 1));
	if (p->category == NULL)
		return NULL;
	strcpy(p->category, category);

	p->quantity = quantity;

	p->expirationDate = (char*)malloc(sizeof(char) * (strlen(expirationDate) + 1));
	if (p->expirationDate == NULL)
		return NULL;
	strcpy(p->expirationDate, expirationDate);

	return p;
}

void destroyProduct(Product* p)
{
	if (p == NULL)
		return;
	free(p->name);
	free(p->category);
	free(p->expirationDate);
	free(p);
}

char* getName(Product* p)
{
	return p->name;
}

char* getCategory(Product* p)
{
	return p->category;
}

int getQuantity(Product* p)
{
	return p->quantity;
}

char* getExpirationDate(Product* p)
{
	return p->expirationDate;
}

void setName(Product* p, char* name)
{
	p->name = (char*)realloc(p->name, sizeof(char) * (strlen(name) + 1));
	strcpy(p->name, name);

}

void setCategory(Product* p, char* category)
{
	p->category = (char*)realloc(p->category, sizeof(char) * (strlen(category) + 1));
	strcpy(p->category, category);
}

void setQuantity(Product* p, int quantity)
{
	p->quantity = quantity;
}

void setExpirationDate(Product* p, char* expirationDate)
{
	p->expirationDate = (char*)realloc(p->expirationDate, sizeof(char) * (strlen(expirationDate) + 1));
	strcpy(p->expirationDate, expirationDate);
}
