#include <stdlib.h>
#include "Repository.h"
#include "Product.h"
#include <string.h>
#include "DynamicArray.h"
Repository* createRepository()
{
	Repository* repo = malloc(sizeof(Repository));
	if (repo == NULL)
		return NULL;
	repo->da = createDynamicArray(1);
	return repo;
}

int findElement(Repository* repo, char* name, char* category)
{
	if (repo->da == NULL)
		return -1;
	int size = getSize(repo->da);
	for (int i = 0; i < size; i++)
	{
		Product* p = repo->da->elems[i];
		if (strcmp(getName(p), name) == 0 && strcmp(getCategory(p), category) == 0)
			return i;
	}
	return -1;
}

void setQuantityToPos(Repository* repo, int quantity, int pos)
{
	if (!(0 <= pos && pos < getSize(repo->da)))
		return;
	setQuantity(repo->da->elems[pos], quantity);
}

int getQuantityOfPos(Repository* repo, int pos)
{
	if (!(0 <= pos && pos < getSize(repo->da)))
		return -1;
	return getQuantity(repo->da->elems[pos]);
}

void destroyRepository(Repository* repo)
{
	if (repo == NULL)
		return;
	destroyArray(repo->da);
	free(repo);
}

void addElement(Repository* repo, TElem* elem)
{
	if (repo->da == NULL)
		return;
	append(repo->da, elem);
}

int deleteElement(Repository* repo, char* name, char* category)
{
	if (repo->da == NULL)
		return 1;
	int size = getSize(repo->da);
	for (int i = 0; i < size; i++)
	{
		Product* p = repo->da->elems[i];
		if (strcmp(getName(p), name) == 0 && strcmp(getCategory(p), category) == 0)
		{
			deleteElementFromArr(repo->da, i);
			return 0;
		}
	}
	return 0;
}


