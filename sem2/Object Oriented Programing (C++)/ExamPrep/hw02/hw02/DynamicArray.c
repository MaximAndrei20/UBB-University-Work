#include "DynamicArray.h"
#include <stdlib.h>
#include "Product.h"

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* arr = malloc(sizeof(DynamicArray));
	arr->elems = malloc(capacity * sizeof(TElem));
	arr->size = 0;
	arr->capacity = capacity;
	return arr;
}

void destroyArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	for (int i = 0; i < arr->size; i++)
		destroyProduct(arr->elems[i]);
	free(arr->elems);
	free(arr);
}

int resize(DynamicArray* arr)
{
	if (arr->size == arr->capacity)
	{
		arr->capacity *= 2;
		TElem* aux = realloc(arr->elems, arr->capacity * sizeof(TElem));
		if (aux == NULL)
		{
			return 1;
		}
		arr->elems = aux;
		return 0;
	}
	return 0;
}



int deleteElementFromArr(DynamicArray* arr, int pos)
{
	destroyProduct(arr->elems[pos]);
	for (int i = pos; i < arr->size - 1; i++)
		arr->elems[i] = arr->elems[i + 1];
	arr->size--;
	return 0;
}

void append(DynamicArray* arr, TElem p)
{
	resize(arr);
	arr->elems[arr->size++] = p;
}

int getSize(DynamicArray* arr)
{
	return arr->size;
}
