#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Repository.h"
#include <time.h>

#define INITIAL_STACK_CAPACITY 10

Service* createService(Repository* repo) {
	Service* s = (Service*)malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = repo;
	s->undoStack = (DynamicArray**)malloc(INITIAL_STACK_CAPACITY * sizeof(DynamicArray*));
	s->undoStackSize = 0;
	s->undoStackCapacity = INITIAL_STACK_CAPACITY;
	s->redoStack = (DynamicArray**)malloc(INITIAL_STACK_CAPACITY * sizeof(DynamicArray*));
	s->redoStackSize = 0;
	s->redoStackCapacity = INITIAL_STACK_CAPACITY;
	return s;
}

void destroyService(Service* s) {
	if (s == NULL)
		return;
	for (int i = 0; i < s->undoStackSize; i++) {
		destroyArray(s->undoStack[i]);
	}
	free(s->undoStack);
	for (int i = 0; i < s->redoStackSize; i++) {
		destroyArray(s->redoStack[i]);
	}
	free(s->redoStack);
	free(s);
}

void saveState(Service* s, DynamicArray*** stack, int* stackSize, int* stackCapacity) {
	if (*stackSize == *stackCapacity) {
		*stackCapacity *= 2;
		*stack = (DynamicArray**)realloc(*stack, *stackCapacity * sizeof(DynamicArray*));
	}
	(*stack)[*stackSize] = createDynamicArray(s->repo->da->capacity);
	for (int i = 0; i < s->repo->da->size; i++) {
		Product* p = s->repo->da->elems[i];
		Product* copy = createProduct(p->name, p->category, p->quantity, p->expirationDate);
		append((*stack)[*stackSize], copy);
	}
	(*stackSize)++;
}

int addProduct(Service* s, char* name, char* category, int quantity, char* expirationDate) {
	saveState(s, &s->undoStack, &s->undoStackSize, &s->undoStackCapacity);
	s->redoStackSize = 0;

	int res = findElement(s->repo, name, category);
	if (res == -1) {
		Product* p = createProduct(name, category, quantity, expirationDate);
		addElement(s->repo, p);
	}
	else {
		setQuantityToPos(s->repo, getQuantityOfPos(s->repo, res) + quantity, res);
	}

	return 0;
}

int deleteProduct(Service* s, char* name, char* category) {
	saveState(s, &s->undoStack, &s->undoStackSize, &s->undoStackCapacity);
	s->redoStackSize = 0;

	int res = deleteElement(s->repo, name, category);
	return res;
}

int updateProduct(Service* s, Product* p, char* newName, char* newCategory, int newQuantity, char* newExpirationDate) {
	if (p == NULL)
		return 1;

	saveState(s, &s->undoStack, &s->undoStackSize, &s->undoStackCapacity);
	s->redoStackSize = 0;

	setName(p, newName);
	setCategory(p, newCategory);
	setQuantity(p, newQuantity);
	setExpirationDate(p, newExpirationDate);
	return 0;
}

void restoreState(Service* s, DynamicArray* state) {
	destroyArray(s->repo->da);
	s->repo->da = createDynamicArray(state->capacity);
	for (int i = 0; i < state->size; i++) {
		Product* p = state->elems[i];
		Product* copy = createProduct(p->name, p->category, p->quantity, p->expirationDate);
		append(s->repo->da, copy);
	}
}

int undo(Service* s) {
	if (s->undoStackSize == 0)
		return 1;

	saveState(s, &s->redoStack, &s->redoStackSize, &s->redoStackCapacity);
	s->undoStackSize--;
	restoreState(s, s->undoStack[s->undoStackSize]);
	destroyArray(s->undoStack[s->undoStackSize]);
	return 0;
}

int redo(Service* s) {
	if (s->redoStackSize == 0)
		return 1;

	saveState(s, &s->undoStack, &s->undoStackSize, &s->undoStackCapacity);
	s->redoStackSize--;
	restoreState(s, s->redoStack[s->redoStackSize]);
	destroyArray(s->redoStack[s->redoStackSize]);
	return 0;
}

int compareProductsByQuantity(const void* a, const void* b) {
	Product* productA = *(Product**)a;
	Product* productB = *(Product**)b;
	return getQuantity(productA) - getQuantity(productB);
}

Product** getSortedProductsByString(Service* s, const char* str, int* outSize) {
	// Create a temporary array to hold the products
	int size = getSize(s->repo->da);
	Product** products = (Product**)malloc(size * sizeof(Product*));
	if (products == NULL) {
		printf("Memory allocation failed\n");
		*outSize = 0;
		return NULL;
	}

	// Copy the products to the temporary array
	int count = 0;
	for (int i = 0; i < size; i++) {
		Product* p = s->repo->da->elems[i];
		if (str[0] == '\0' || strstr(getName(p), str) != NULL) {
			products[count++] = p;
		}
	}

	// Sort the products by quantity
	qsort(products, count, sizeof(Product*), compareProductsByQuantity);

	*outSize = count;
	return products;
}

// Custom strptime function for Windows
char* strptime(const char* s, const char* format, struct tm* tm) {
	memset(tm, 0, sizeof(struct tm));
	sscanf(s, "%d.%d.%d", &tm->tm_mday, &tm->tm_mon, &tm->tm_year);
	tm->tm_mon -= 1;
	tm->tm_year -= 1900;
	return (char*)(s + strlen(s));
}

// Function to parse date string in the format "dd.mm.yyyy"
time_t parseDate(const char* dateStr) {
	struct tm time;
	memset(&time, 0, sizeof(struct tm));
	strptime(dateStr, "%d.%m.%Y", &time);
	return mktime(&time);
}

// Function to calculate the date X days from now
time_t calculateTargetDate(int days) {
	time_t now = time(NULL);
	return now + days * 24 * 60 * 60;
}

Product** getProductsByCategoryAndExpiration(Service* s, const char* category, int days, int* outSize) {
	time_t targetDate = calculateTargetDate(days);

	// Create a temporary array to hold the products
	int size = getSize(s->repo->da);
	Product** products = (Product**)malloc(size * sizeof(Product*));
	if (products == NULL) {
		printf("Memory allocation failed\n");
		*outSize = 0;
		return NULL;
	}

	// Copy the products to the temporary array
	int count = 0;
	for (int i = 0; i < size; i++) {
		Product* p = s->repo->da->elems[i];
		time_t expirationDate = parseDate(getExpirationDate(p));

		if ((category[0] == '\0' || strcmp(getCategory(p), category) == 0) && expirationDate <= targetDate) {
			products[count++] = p;
		}
	}

	*outSize = count;
	return products;
	return NULL;
}
